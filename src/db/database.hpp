#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "basedb.hpp"

#include "Model.hpp"
#include "dto/MyDTOs.hpp"

#include <any>

namespace koloboot {
namespace db {

enum type_dto {
    user = 0,
    login = 1
};

struct User {
    constexpr static const char* collection = "donasi";
};

struct Muhsinin {
    constexpr static const char* collection = "muhsinin";
};

struct Rekap {
    constexpr static const char* collection = "rekap";
};

template <const char* T>
struct CountCondition {
    enum {
        value = T
    };
};

class Database: public koloboot::db::BaseDB
{

public:
    Database(const mongocxx::uri& uri, const std::string& db_name, const std::string& collection_name);
private:
    oatpp::Object<koloboot::db::DonaturModel> donaturDromDto(const oatpp::Object<DonaturDto>& dto);
    oatpp::Object<DonaturDto> dtoFromDonatur(const oatpp::Object<koloboot::db::DonaturModel>& donatur);
    oatpp::Object<koloboot::db::UserModel> userFromDto(const oatpp::Object<UserDto>& dto);
    std::any dtoFromUser(const oatpp::Object<koloboot::db::UserModel>& user, koloboot::db::type_dto type = koloboot::db::type_dto::user);
    oatpp::Object<koloboot::db::RekapModel> rekapFromDto(const oatpp::Object<RekapDto>& dto);
    oatpp::Object<RekapDto> dtoFromRekap(const oatpp::Object<RekapModel>& rekap);
public:
    oatpp::Object<DonaturDto> createDonatur(const oatpp::Object<DonaturDto>& donatur_dto);
    oatpp::Object<DonaturDto> updateDonatur(const oatpp::Object<DonaturDto>& donatur_dto);
    oatpp::Object<DonaturDto> getDonatur(std::string_view alias);
    oatpp::List<oatpp::Object<DonaturDto>> getAllDonatur();

    oatpp::Object<UserDto> createUser(const oatpp::Object<UserDto>& user_dto);
    oatpp::Object<LoginDto> login(const oatpp::Object<UserDto>& user_dto);
    bool deleteDonatur(std::string_view alias);
    bool usernameIsExists(std::string_view username);
    oatpp::Object<RekapDto> createRekap(const oatpp::Object<RekapDto>& rekap_dto);
    oatpp::Object<RekapDto> updateRekap(const oatpp::Object<RekapDto>& rekap_dto);
    bool deleteRekap(std::string_view kode);
    bool rekapIsExists(const oatpp::Object<RekapDto>& rekap_dto);
    oatpp::List<oatpp::Object<RekapDto>> getAllRekap();

    size_t donaturCount(std::string_view condition = "");
};
}
}

#endif // DATABASE_HPP
