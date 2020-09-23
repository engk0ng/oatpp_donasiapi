#ifndef APPCOMPONENT_HPP
#define APPCOMPONENT_HPP

#include "oatpp/web/server/AsyncHttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/network/server/SimpleTCPConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"

#include "db/database.hpp"

#include <mongocxx/client.hpp>

class AppComponent {
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor)([]{
        return std::make_shared<oatpp::async::Executor>();
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([]{
        return oatpp::network::server::SimpleTCPConnectionProvider::createShared(8787);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([]{
        return oatpp::web::server::HttpRouter::createShared();
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::server::ConnectionHandler>, serverConnectionHandler)([]{
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
        OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor);
        return oatpp::web::server::AsyncHttpConnectionHandler::createShared(router, executor);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([]{
        auto serializerConfig = oatpp::parser::json::mapping::Serializer::Config::createShared();
        auto deserializerConfig = oatpp::parser::json::mapping::Deserializer::Config::createShared();
        deserializerConfig->allowUnknownFields = false;
        auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared(serializerConfig, deserializerConfig);
        return objectMapper;
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<koloboot::db::Database>, database)([]{
        mongocxx::uri uri {""};
        return std::make_shared<koloboot::db::Database>(uri, "", "");
    }());
};

#endif // APPCOMPONENT_HPP
