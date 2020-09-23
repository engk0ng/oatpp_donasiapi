#include "basedb.hpp"

namespace koloboot {
namespace db {
BaseDB::BaseDB(const mongocxx::uri& uri, const std::string& db_name, const std::string& collection_name):
    m_pool(std::make_shared<mongocxx::pool>(uri)), m_database_name(db_name), m_collection_name(collection_name)
{

}

bsoncxx::document::value BaseDB::createMongoDocument(const oatpp::Void &polymorph) {
    oatpp::data::stream::BufferOutputStream stream;
    m_object_mapper.write(&stream, polymorph);
    bsoncxx::document::view view(stream.getData(), stream.getCurrentPosition());
    return bsoncxx::document::value(view);
}
}
}

