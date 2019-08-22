#include "command-controller.h"

#include <QList>
#include <QDebug>

using namespace cm::framework;

namespace cm {
namespace controllers {

class CommandController::Implementation {
public:
    Implementation(CommandController* _controller)
        : controller(_controller){

        auto* createClientSaveCommand = new Command(controller, QChar(0xf0c7), "Save");
        QObject::connect(createClientSaveCommand, &Command::execute, controller,
                         &CommandController::onCreateClientSaveExecuted);
        createClientViewContextCommands.append(createClientSaveCommand);
    }

    CommandController* controller{};
    QList<Command*> createClientViewContextCommands{};
};

CommandController::CommandController(QObject *parent) : QObject(parent) {
    impl.reset(new Implementation(this));
}

CommandController::~CommandController() {}

QQmlListProperty<Command> CommandController::ui_createClientViewContextCommands() {
    return QQmlListProperty<Command>(this, impl->createClientViewContextCommands);
}

void CommandController::onCreateClientSaveExecuted() {
    qDebug() << "Save command executed!";
}

}}
