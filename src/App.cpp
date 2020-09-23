#include "controller/mycontroller.hpp"

#include "./AppComponent.hpp"


#include "oatpp/network/server/Server.hpp"


#include <mongocxx/instance.hpp>


#include <iostream>

void run() {
    mongocxx::instance instance{};

    AppComponent components;

    auto router = components.httpRouter.getObject();

    auto my_controller = MyController::createShared();
    my_controller->addEndpointsToRouter(router);

    oatpp::network::server::Server server(components.serverConnectionProvider.getObject(),
                                          components.serverConnectionHandler.getObject());

    OATPP_LOGD("Server", "Running on port %s...", components.serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());

    server.run();
}

int main(int argc, const char * argv[]) {

    oatpp::base::Environment::init();

    run();

    /* Print how much objects were created during app running, and what have left-probably leaked */
    /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

    oatpp::base::Environment::destroy();

    return 0;
}

