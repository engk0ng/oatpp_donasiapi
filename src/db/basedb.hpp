#ifndef BASEDB_HPP
#define BASEDB_HPP

#include <string_view>

#include "oatpp-mongo/bson/mapping/ObjectMapper.hpp"

#include <mongocxx/pool.hpp>
#include <bsoncxx/document/value.hpp>

namespace koloboot {
namespace db {
class BaseDB
{
protected:
    std::shared_ptr<mongocxx::pool> m_pool;
    std::string m_database_name;
    std::string m_collection_name;
    oatpp::mongo::bson::mapping::ObjectMapper m_object_mapper;
protected:
    bsoncxx::document::value createMongoDocument(const oatpp::Void &polymorph);
public:
    BaseDB(const mongocxx::uri& uri, const std::string& db_name, const std::string& collection_name);
};
}
}

#endif // BASEDB_HPP
