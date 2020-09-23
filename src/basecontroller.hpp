#ifndef BASECONTROLLER_HPP
#define BASECONTROLLER_HPP

#include "oatpp/web/server/api/ApiController.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <functional>

#include "dto/MyDTOs.hpp"

#include <jwt.h>

struct VerifContent {
    constexpr static const short type = 1;
};

struct VerifAuth {
    constexpr static const short type = 2;
};

class BaseController: public oatpp::web::server::api::ApiController
{
protected:
    BaseController(const std::shared_ptr<ObjectMapper>& object_mapper):
        oatpp::web::server::api::ApiController(object_mapper) {}

    static std::vector<std::string> splitString(const std::string& str, std::string_view token) {
        std::vector<std::string> list {};
        std::istringstream stream(str.c_str());
        std::string m_str;

        while (std::getline(stream, m_str, token.at(0))) {
            list.emplace_back(m_str);
        }
        return list;
    }

    static void verifikasiRequest(const std::shared_ptr<IncomingRequest>& req,
                                  std::function<void(oatpp::Object<MessageDto>, Status)> callback,
                                  int type = VerifContent::type) {
        oatpp::Object<MessageDto> message = nullptr;
        Status status = Status::CODE_102;
        if (type < VerifAuth::type) {
            if (req->getHeader("Content-Type") != "application/json") {
                message = MessageDto::createShared();
                message->code = 415;
                message->message = "Content tidak valid";
                status = Status::CODE_415;
            }
        }
        else {
            if (req->getHeader("Content-Type") != "application/json") {
                message = MessageDto::createShared();
                message->code = 415;
                message->message = "Content tidak valid";
                status = Status::CODE_415;
            }
            else {
                std::string bearer = req->getHeader("Authorization")->c_str();
                if (bearer == "") {
                    message = MessageDto::createShared();
                    message->code = 401;
                    message->message = "Anda tidak memiliki hak akses";
                    status = Status::CODE_401;
                }
                else {
                    std::vector<std::string> splist = splitString(bearer, " ");
                    if (splist.size() < 2) {
                        message = MessageDto::createShared();
                        message->code = 401;
                        message->message = "Anda tidak memiliki hak akses";
                        status = Status::CODE_401;
                    }
                    else {
                        std::string authorization = splist.at(1);
                        auto decoded = jwt::decode(authorization);
                        auto expire = decoded.get_expires_at();
                        auto different = expire - std::chrono::system_clock::now();
                        if (different.count() < 7200) {
                            message = MessageDto::createShared();
                            message->code = 401;
                            message->message = "Token anda sudah expire";
                            status = Status::CODE_401;
                        }
                        else {

                        }
                    }
                }
            }
        }

        callback(message, status);
    }
};

#endif // BASECONTROLLER_HPP
