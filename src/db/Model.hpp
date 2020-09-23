#ifndef MODEL_HPP
#define MODEL_HPP

#include "dto/MyDTOs.hpp"

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace koloboot {
namespace db {

class DonaturModel: public oatpp::DTO {
    DTO_INIT(DonaturModel, DTO)

    DTO_FIELD(Any, _id);
    DTO_FIELD(String, nama);
    DTO_FIELD(String, alias);
};

class UserModel: public oatpp::DTO {
    DTO_INIT(UserModel, DTO)

    DTO_FIELD(Any, _id);
    DTO_FIELD(String, nama);
    DTO_FIELD(String, username);
    DTO_FIELD(String, password);
};

class LoginModel: public oatpp::DTO {
    DTO_INIT(LoginModel, DTO)

    DTO_FIELD(Any, _id);
    DTO_FIELD(String, nama);
    DTO_FIELD(String, username);
    DTO_FIELD(String, password);
    DTO_FIELD(String, token);
};

class RekapModel: public oatpp::DTO {
    DTO_INIT(RekapModel, DTO)

    DTO_FIELD(Any, _id);
    DTO_FIELD(String, kode);
    DTO_FIELD(String, nama);
    DTO_FIELD(Int64, nominal);
};
}
}

#include OATPP_CODEGEN_END(DTO)

#endif // MODEL_HPP
