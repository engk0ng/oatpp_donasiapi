#ifndef MYDTOS_HPP
#define MYDTOS_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class HelloDto: public oatpp::DTO {
    DTO_INIT(HelloDto, DTO)

    DTO_FIELD(String, userAgent, "user-agent");
    DTO_FIELD(String, message);
    DTO_FIELD(String, server);
};

class MessageDto: public oatpp::DTO {
    DTO_INIT(MessageDto, DTO)
    DTO_FIELD(Int16, code);
    DTO_FIELD(String, message);
    DTO_FIELD(Any, data);
};

class DonaturDto: public oatpp::DTO {
    DTO_INIT(DonaturDto, DTO)

    DTO_FIELD(String, nama);
    DTO_FIELD(String, alias);
};

class UserDto: public oatpp::DTO {
    DTO_INIT(UserDto, DTO)

    DTO_FIELD(String, nama);
    DTO_FIELD(String, username);
    DTO_FIELD(String, password);
};

class LoginDto: public oatpp::DTO {
    DTO_INIT(LoginDto, DTO)

    DTO_FIELD(String, nama);
    DTO_FIELD(String, username);
    DTO_FIELD(String, password);
    DTO_FIELD(String, token);
};

class RekapDto: public oatpp::DTO {
    DTO_INIT(RekapDto, DTO)

    DTO_FIELD(String, kode);
    DTO_FIELD(String, nama);
    DTO_FIELD(Int64, nominal);
};
#include OATPP_CODEGEN_END(DTO)

#endif // MYDTOS_HPP
