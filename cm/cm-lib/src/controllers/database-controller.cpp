#include "database-controller.h"

#include <QDebug>
#include <QJsonDocument>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

namespace cm {
namespace controllers {

class DatabaseController::Implementation {

public:
    Implementation(DatabaseController* controller)
        : controller(controller) {

        if (initialise()) {
            qDebug() << "Database created using Sqlite version: " << sqliteVersion();
            if (createTables()) {
                qDebug() << "Database tables created";
            } else {
                qDebug() << "ERROR: Unable to create database tables";
            }
        } else {
            qDebug() << "ERROR: Unable to open database";
        }
    }

    DatabaseController* controller{nullptr};
    QSqlDatabase database;

private:
    bool initialise() {
        database = QSqlDatabase::addDatabase("QSQLITE", "cm");
        database.setDatabaseName("cm.sqlite");
        return database.open();
    }

    bool createTables() {
        return createJsonTable("client");
    }

    bool createJsonTable(const QString& tableName) const {
        QSqlQuery query(database);
        QString sqlStatement = "CREATE TABLE IF NOT EXISTS " + tableName +
                               " (id text primary key, json text not null)";

        if (!query.prepare(sqlStatement)) {
            return false;
        }
        return query.exec();
    }

    QString sqliteVersion() const {
        QSqlQuery query(database);
        query.exec("SELECT sqlite_version()");
        if (query.next()) {
            return query.value(0).toString();
        }
        return QString::number(-1);
    }
};

DatabaseController::DatabaseController(QObject* parent)
    : IDatabaseController(parent) {
    impl.reset(new Implementation(this));
}

DatabaseController::~DatabaseController() {}

bool DatabaseController::createRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const {

    if (tableName.isEmpty() || id.isEmpty() || jsonObject.isEmpty()) {
        return false;
    }
    QSqlQuery query(impl->database);
    QString sqlStatement = "INSERT OR REPLACE INTO " + tableName + " (id, json) VALUES (:id, :json)";

    if (!query.prepare(sqlStatement)) {
        return false;
    }
    query.bindValue(":id", QVariant(id));
    query.bindValue(":json", QVariant(QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)));
    return query.exec() && query.numRowsAffected() > 0;
}

bool DatabaseController::deleteRow(const QString& tableName, const QString& id) const {

    if (tableName.isEmpty() || id.isEmpty()) {
        return false;
    }
    QSqlQuery query(impl->database);
    QString sqlStatement = "DELETE FROM " + tableName + " WHERE id=:id";

    if (!query.prepare(sqlStatement)) {
        return false;
    }
    query.bindValue(":id", QVariant(id));
    return query.exec() && query.numRowsAffected() > 0;
}

QJsonObject DatabaseController::readRow(const QString& tableName, const QString& id) const {

    if (tableName.isEmpty() || id.isEmpty()) {
        return {};
    }
    QSqlQuery query(impl->database);
    QString sqlStatement = "SELECT json FROM " + tableName + " WHERE id=:id";

    if (!query.prepare(sqlStatement)) {
        return {};
    }
    query.bindValue(":id", QVariant(id));

    if (!query.exec() || !query.first()) {
        return {};
    }
    auto json = query.value(0).toByteArray();
    auto jsonDocument = QJsonDocument::fromJson(json);

    if (!jsonDocument.isObject()) {
        return {};
    }
    return jsonDocument.object();
}

bool DatabaseController::updateRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const {

    if (tableName.isEmpty() || id.isEmpty() || jsonObject.isEmpty()) {
        return false;
    }
    QSqlQuery query(impl->database);
    QString sqlStatement = "UPDATE " + tableName + " SET json=:json WHERE id=:id";

    if (!query.prepare(sqlStatement)) {
        return false;
    }
    query.bindValue(":id", QVariant(id));
    query.bindValue(":json", QVariant(QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)));
    return query.exec() && query.numRowsAffected() > 0;
}

QJsonArray DatabaseController::find(const QString& tableName, const QString& searchText) const {

    if (tableName.isEmpty() || searchText.isEmpty()) {
        return {};
    }
    QSqlQuery query(impl->database);
    QString sqlStatement = "SELECT json FROM " + tableName + " where lower(json) like :searchText";

    if (!query.prepare(sqlStatement)) {
        return {};
    }
    query.bindValue(":searchText", QVariant("%" + searchText.toLower() + "%"));
    if (!query.exec()) {
        return {};
    }
    QJsonArray returnValue;
    while (query.next()) {
        auto json = query.value(0).toByteArray();
        auto jsonDocument = QJsonDocument::fromJson(json);
        if (jsonDocument.isObject()) {
            returnValue.append(jsonDocument.object());
        }
    }
    return returnValue;
}

}}
