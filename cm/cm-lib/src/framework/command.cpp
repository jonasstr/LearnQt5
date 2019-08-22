#include "command.h"

namespace cm {
namespace framework {

class Command::Implementation {
public:
    Implementation(QString iconCharacter, QString description, std::function<bool()> canExecute)
        : iconCharacter(iconCharacter),
          description(description),
          canExecute(canExecute) {}

    QString iconCharacter;
    QString description;
    std::function<bool()> canExecute;
};

Command::Command(QObject *parent, const QString& iconCharacter, const QString& description,
                 std::function<bool()> canExecute) : QObject(parent) {

    impl.reset(new Implementation(iconCharacter, description, canExecute));
}

Command::~Command() {}

const QString& Command::iconCharacter() const {
    return impl->iconCharacter;
}

const QString& Command::description() const {
    return impl->description;
}

bool Command::canExecute() const {
    return impl->canExecute();
}

}}

