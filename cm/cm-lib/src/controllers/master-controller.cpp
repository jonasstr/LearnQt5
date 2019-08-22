#include "master-controller.h"

namespace cm {
namespace controllers {

class MasterController::Implementation {
public:
    Implementation(MasterController* controller)
        : masterController(controller) {
        commandController = new CommandController(masterController);
        navigationController = new NavigationController(masterController);
    }

    MasterController* masterController{};
    CommandController* commandController{};
    NavigationController* navigationController{};
    QString welcomeMessage = "Hello there, General Kenobi!";
};

MasterController::MasterController(QObject *parent) : QObject(parent) {
    impl.reset(new Implementation(this));
}

MasterController::~MasterController() {}

CommandController* MasterController::commandController() {
    return impl->commandController;
}

NavigationController* MasterController::navigationController() {
    return impl->navigationController;
}

const QString& MasterController::welcomeMessage() const {
    return impl->welcomeMessage;
}

}}
