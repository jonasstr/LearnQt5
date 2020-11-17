#include "command-controller.h"

#include <QList>
#include <QDebug>

using namespace cm::framework;

namespace cm {
namespace controllers {

class CommandController::Implementation {
public:
    Implementation(CommandController* commandController, IDatabaseController* databaseController, models::Client* client)
        : commandController(commandController), databaseController(databaseController), client(client) {

        auto* createClientSaveCommand = new Command(commandController, QChar(0xf0c7), "Save");
        QObject::connect(createClientSaveCommand, &Command::execute, commandController,
                         &CommandController::onCreateClientSaveExecuted);
        createClientViewContextCommands.append(createClientSaveCommand);
    }

    CommandController* commandController{};
    QList<Command*> createClientViewContextCommands{};
    IDatabaseController* databaseController{};
    models::Client* client{};
};

CommandController::CommandController(QObject *parent, IDatabaseController* databaseController, models::Client* client) : QObject(parent) {
    impl.reset(new Implementation(this, databaseController, client));
}

CommandController::~CommandController() {}

QQmlListProperty<Command> CommandController::ui_createClientViewContextCommands() {
    return QQmlListProperty<Command>(this, impl->createClientViewContextCommands);
}

void CommandController::onCreateClientSaveExecuted() {
    qDebug() << "Save command executed!";
    impl->databaseController->createRow(impl->client->key(), impl->client->id(), impl->client->toJson());
    qDebug() << "New client saved.";
}

}}
