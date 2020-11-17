#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include "framework/command.h"
#include "i-database-controller.h"
#include "models/client.h"

#include <QObject>
#include <QtQml/QQmlListProperty>
#include <cm-lib_global.h>

namespace cm {
namespace controllers {

class CMLIBSHARED_EXPORT CommandController : public QObject {

    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_createClientViewContextCommands
               READ ui_createClientViewContextCommands CONSTANT)

public:
    explicit CommandController(QObject *parent = nullptr, IDatabaseController* controller = nullptr,
                               models::Client* client = nullptr);
    ~CommandController();

    QQmlListProperty<framework::Command> ui_createClientViewContextCommands();

public slots:
    void onCreateClientSaveExecuted();

private:
    class Implementation;
    QScopedPointer<Implementation> impl;

};

}}

#endif // COMMANDCONTROLLER_H
