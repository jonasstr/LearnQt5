#include "master-controller.h"

#include "database-controller.h"

namespace cm {
namespace controllers {

class MasterController::Implementation {
public:
    Implementation(MasterController* controller)
        : masterController(controller) {

        databaseController = new DatabaseController(masterController);
        commandController = new CommandController(masterController);
        navigationController = new NavigationController(masterController);
        newClient = new Client(masterController);
    }

    DatabaseController* databaseController;
    MasterController* masterController;
    CommandController* commandController;
    NavigationController* navigationController;
    Client* newClient;

    QString welcomeMessage = "Welcome to the Client Management system!";
};

MasterController::MasterController(QObject *parent) : QObject(parent) {
    impl.reset(new Implementation(this));
}

MasterController::~MasterController() {}

DatabaseController* MasterController::databaseController() {
    return impl->databaseController;
}

CommandController* MasterController::commandController() {
    return impl->commandController;
}

NavigationController* MasterController::navigationController() {
    return impl->navigationController;
}

Client*MasterController::newClient() {
    return impl->newClient;
}

const QString& MasterController::welcomeMessage() const {
    return impl->welcomeMessage;
}

}}
