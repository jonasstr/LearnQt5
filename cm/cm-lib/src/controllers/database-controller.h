#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include "controllers/i-database-controller.h"

#include <cm-lib_global.h>
#include <QScopedPointer>

namespace cm {
namespace controllers {

class DatabaseController : public IDatabaseController {

    Q_OBJECT

public:
    explicit DatabaseController(QObject* parent = nullptr);
    ~DatabaseController();

    bool createRow(const QString &tableName, const QString &id, const QJsonObject &jsonObject) const override;
    bool deleteRow(const QString &tableName, const QString &id) const override;
    QJsonArray find(const QString &tableName, const QString &searchText) const override;
    QJsonObject readRow(const QString &tableName, const QString &id) const override;
    bool updateRow(const QString &tableName, const QString &id, const QJsonObject &jsonObject) const override;

private:
    class Implementation;
    QScopedPointer<Implementation> impl;
};

}}

#endif // DATABASECONTROLLER_H
