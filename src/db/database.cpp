#include "database.hpp"

#include "oatpp/core/data/stream/BufferStream.hpp"

#include <mongocxx/client.hpp>
#include <mongocxx/options/index.hpp>
#include <mongocxx/exception/operation_exception.hpp>

#include <jwt.h>

#include "sha256.hpp"

namespace koloboot {
namespace db {
Database::Database(const mongocxx::uri& uri, const std::string& db_name, const std::string& collection_name)
    :BaseDB(uri, db_name, collection_name)
{}

oatpp::Object<koloboot::db::DonaturModel> Database::donaturDromDto(const oatpp::Object<DonaturDto> &dto) {
    auto donatur = koloboot::db::DonaturModel::createShared();
    donatur->_id = dto->alias;
    donatur->alias = dto->alias;
    donatur->nama = dto->nama;
    return donatur;
}

oatpp::Object<koloboot::db::UserModel> Database::userFromDto(const oatpp::Object<UserDto> &dto) {
    auto user = koloboot::db::UserModel::createShared();
    user->_id = dto->username;
    user->username = dto->username;
    user->password = dto->password;
    return user;
}

oatpp::Object<DonaturDto> Database::dtoFromDonatur(const oatpp::Object<koloboot::db::DonaturModel> &donatur) {
    auto dto = DonaturDto::createShared();
    dto->alias = donatur->alias;
    dto->nama = donatur->nama;
    return dto;
}

oatpp::Object<RekapDto> Database::dtoFromRekap(const oatpp::Object<RekapModel> &rekap) {
    auto dto = RekapDto::createShared();
    dto->kode = rekap->kode;
    dto->nama = rekap->nama;
    dto->nominal = rekap->nominal;
    return dto;
}

oatpp::Object<RekapModel> Database::rekapFromDto(const oatpp::Object<RekapDto> &dto) {
    auto rekap = RekapModel::createShared();
    rekap->_id = dto->kode;
    rekap->nama = dto->nama;
    rekap->nominal = dto->nominal;
    rekap->kode = dto->kode;
    return rekap;
}

std::any Database::dtoFromUser(const oatpp::Object<koloboot::db::UserModel> &user, koloboot::db::type_dto type) {
    std::any res = nullptr;
    if (type == koloboot::db::type_dto::user) {
        auto dto = UserDto::createShared();
        dto->username = user->username;
        dto->password = user->password;
        dto->nama = user->nama;
        res = dto;
    }
    else {
        auto log = LoginDto::createShared();
        log->username = user->username;
        log->nama = user->nama;
        log->password ="";
        auto token = jwt::create()
        .set_id("koloboot-3mb3-3nak")
        .set_issuer("auth0")
        .set_type("JWS")
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{7200})
        .set_payload_claim("username", jwt::claim(std::string(user->username->c_str())))
        .sign(jwt::algorithm::hs256{"secret"});
        log->token = token.c_str();
        res = log;
    }
    return res;
}

oatpp::Object<DonaturDto> Database::createDonatur(const oatpp::Object<DonaturDto> &donatur_dto) {
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][Muhsinin::collection];
    collection.insert_one(createMongoDocument(donaturDromDto(donatur_dto)));
    return donatur_dto;
}

oatpp::Object<UserDto> Database::createUser(const oatpp::Object<UserDto> &user_dto) {
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][User::collection];
    collection.insert_one(createMongoDocument(userFromDto(user_dto)));
    return user_dto;
}

oatpp::Object<DonaturDto> Database::updateDonatur(const oatpp::Object<DonaturDto> &donatur_dto) {
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][Muhsinin::collection];
    oatpp::Fields<oatpp::String> where_list = oatpp::Fields<oatpp::String>({{"alias", donatur_dto->alias}});
    oatpp::Fields<oatpp::Any> set_list = oatpp::Fields<oatpp::Any>({
            {"$set", oatpp::Fields<oatpp::Any>({
                                                       {"nama", donatur_dto->nama}
                                               })
            }
            });
    auto result = collection.update_one(createMongoDocument(where_list), createMongoDocument(set_list));
    if (result->matched_count() == 1)
        return donatur_dto;
    else
        return nullptr;
}

oatpp::Object<DonaturDto> Database::getDonatur(std::string_view alias) {
    oatpp::String m_alias = oatpp::String(alias.data());
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][Muhsinin::collection];
    oatpp::Fields<oatpp::String> where_list = oatpp::Fields<oatpp::String>({{"_id", m_alias}});
    auto result = collection.find_one(createMongoDocument(where_list));
    if (result) {
        auto view = result->view();
        auto bson = oatpp::String((const char *)view.data(), view.length(), false);
        auto donatur = m_object_mapper.readFromString<oatpp::Object<koloboot::db::DonaturModel>>(bson);
        return dtoFromDonatur(donatur);
    }
    return nullptr;
}

oatpp::List<oatpp::Object<DonaturDto>> Database::getAllDonatur() {
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][Muhsinin::collection];
    bsoncxx::document::view_or_value vl = createMongoDocument(oatpp::Fields<oatpp::String>({}));
    auto cursor = collection.find(vl);
    oatpp::List<oatpp::Object<DonaturDto>> list({});
    for (auto& view: cursor) {
        auto bson = oatpp::String((const char*)view.data(), view.length(), false);
        auto donatur = m_object_mapper.readFromString<oatpp::Object<koloboot::db::DonaturModel>>(bson);
        list->push_back(dtoFromDonatur(donatur));
    }
    return list;
}

bool Database::deleteDonatur(std::string_view alias) {
    oatpp::String m_alias = oatpp::String(alias.data());
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][Muhsinin::collection];
    oatpp::Fields<oatpp::String> where_list = oatpp::Fields<oatpp::String>({{"alias", m_alias}});
    bsoncxx::document::view_or_value where_vov = createMongoDocument(where_list);
    auto result = collection.delete_one(where_vov);
    if (result) {
        return result->deleted_count() == 1;
    }
    return false;
}

oatpp::Object<LoginDto> Database::login(const oatpp::Object<UserDto> &user_dto) {
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][User::collection];
    oatpp::Fields<oatpp::String> where_list = oatpp::Fields<oatpp::String>({{"username", user_dto->username},
                                                                            {"password", sha256(user_dto->password->c_str()).c_str()}});
    auto result = collection.find_one(createMongoDocument(where_list));
    if (result) {
        auto view = result->view();
        auto bson = oatpp::String((const char*)view.data(), view.length(), false);
        auto user = m_object_mapper.readFromString<oatpp::Object<koloboot::db::UserModel>>(bson);
        auto user_from_dto = dtoFromUser(user);
        auto usr = std::any_cast<oatpp::Object<UserDto>>(user_from_dto);
        return std::any_cast<oatpp::Object<LoginDto>>(dtoFromUser(user, koloboot::db::type_dto::login));
    }
    return nullptr;
}

bool Database::usernameIsExists(std::string_view username) {
    oatpp::String usr = oatpp::String(username.data());
    auto con = m_pool->acquire();
    auto collection = (*con)[m_database_name][User::collection];
    oatpp::Fields<oatpp::String> where_list = oatpp::Fields<oatpp::String>({{"username", usr}});
    bsoncxx::document::view_or_value where_vov = createMongoDocument(where_list);
    auto result = collection.count_documents(where_vov);
    if (result > 0) {
        return true;
    }
    return false;
}

std::size_t Database::donaturCount(std::string_view condition) {
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][Muhsinin::collection];
    if (condition != "") {
        oatpp::String alias = oatpp::String(condition.data());
        oatpp::Fields<oatpp::String> where_list = oatpp::Fields<oatpp::String>({{"alias", alias}});
        bsoncxx::document::view_or_value where_vov = createMongoDocument(where_list);
        auto result = collection.count_documents(where_vov);
        return result;
    }
    else {
        oatpp::Fields<oatpp::String> where_list = oatpp::Fields<oatpp::String>({{}});
        bsoncxx::document::view_or_value where_vov = createMongoDocument(where_list);
        auto result = collection.count_documents(where_vov);
        return result;
    }
}

bool Database::rekapIsExists(const oatpp::Object<RekapDto> &rekap_dto) {
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][Rekap::collection];
    oatpp::Fields<oatpp::String> where_list = oatpp::Fields<oatpp::String>({{"kode", rekap_dto->kode}});
    bsoncxx::document::view_or_value where_vov = createMongoDocument(where_list);
    auto result = collection.count_documents(where_vov);
    if (result > 0)
        return true;
    else
        return false;
}

oatpp::Object<RekapDto> Database::createRekap(const oatpp::Object<RekapDto> &rekap_dto) {
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][Rekap::collection];
    collection.insert_one(createMongoDocument(rekapFromDto(rekap_dto)));
    return rekap_dto;
}

oatpp::Object<RekapDto> Database::updateRekap(const oatpp::Object<RekapDto> &rekap_dto) {
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][Rekap::collection];
    oatpp::Fields<oatpp::String> where_list = oatpp::Fields<oatpp::String>({{"kode", rekap_dto->kode}});
    oatpp::Fields<oatpp::Any> set_list = oatpp::Fields<oatpp::Any>({
        {"$set", oatpp::Fields<oatpp::Any> ({
            {"nama", rekap_dto->nama},
            {"nominal", rekap_dto->nominal}
        })
        }
    });
    auto result = collection.update_one(createMongoDocument(where_list), createMongoDocument(set_list));
    if (result->matched_count() == 1) {
        return rekap_dto;
    } else
        return nullptr;
}

bool Database::deleteRekap(std::string_view kode) {
    oatpp::String m_kode = oatpp::String(kode.data());
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][Rekap::collection];
    oatpp::Fields<oatpp::String> where_list = oatpp::Fields<oatpp::String>({{"kode", m_kode}});
    bsoncxx::document::view_or_value where_vov = createMongoDocument(where_list);
    auto result = collection.delete_one(where_vov);
    if (result) {
        return result->deleted_count() == 1;
    }
    return false;
}

oatpp::List<oatpp::Object<RekapDto>> Database::getAllRekap() {
    auto conn = m_pool->acquire();
    auto collection = (*conn)[m_database_name][Rekap::collection];
    bsoncxx::document::view_or_value vl = createMongoDocument(oatpp::Fields<oatpp::String>({}));
    auto cursor = collection.find(vl);
    oatpp::List<oatpp::Object<RekapDto>> list({});
    for (auto& view: cursor) {
        auto bson = oatpp::String((const char*)view.data(), view.length(), false);
        auto rekap = m_object_mapper.readFromString<oatpp::Object<koloboot::db::RekapModel>>(bson);
        list->push_back(dtoFromRekap(rekap));
    }
    return list;
}
}
}


