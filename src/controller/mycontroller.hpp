#ifndef MYCONTROLLER_HPP
#define MYCONTROLLER_HPP

#include "db/database.hpp"

#include "dto/MyDTOs.hpp"

#include "basecontroller.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/data/stream/BufferStream.hpp"

#include "sha256.hpp"

#include <jwt.h>

#include OATPP_CODEGEN_BEGIN(ApiController)

class MyController: public BaseController {
protected:
    MyController(const std::shared_ptr<ObjectMapper> &object_mapper) :
            BaseController(object_mapper) {}

public:
    static std::shared_ptr<MyController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::shared_ptr<MyController>(new MyController(objectMapper));
    }

    ENDPOINT_ASYNC("GET", "/", Root) {
    ENDPOINT_ASYNC_INIT(Root)

        Action act() override {
            auto dto = HelloDto::createShared();
            dto->message = "Hello Async!";
            dto->server = Header::Value::SERVER;
            dto->userAgent = request->getHeader(Header::USER_AGENT);
            return _return(controller->createDtoResponse(Status::CODE_200, dto));
        }
    };

    ENDPOINT_ASYNC("GET", "/body/string", EchoStringBody) {
    ENDPOINT_ASYNC_INIT(EchoStringBody)

        Action act() override {
            return request->readBodyToStringAsync().callbackTo(&EchoStringBody::returnResponse);
        }

        Action returnResponse(const oatpp::String &body) {
            return _return(controller->createResponse(Status::CODE_200, body));
        }
    };

    ENDPOINT_ASYNC("GET", "/body/dto", EchoDtoBody) {
    ENDPOINT_ASYNC_INIT(EchoDtoBody)

        Action act() override {
            return request->readBodyToDtoAsync<oatpp::Object<MessageDto>>(
                    controller->getDefaultObjectMapper()).callbackTo(&EchoDtoBody::returnResponse);
        }

        Action returnResponse(const oatpp::Object<MessageDto> &body) {
            return _return(controller->createDtoResponse(Status::CODE_200, body));
        }
    };

    ENDPOINT_ASYNC("POST", "/api/user/create", CreateUser) {
    ENDPOINT_ASYNC_INIT(CreateUser)

        Action act() override {
            oatpp::Object<MessageDto> message = nullptr;
            Status status = Status::CODE_200;
            verifikasiRequest(request, [&message, &status](oatpp::Object<MessageDto> m, Status stat) {
                message = m;
                status = stat;
            }, VerifContent::type);
            if (message != nullptr) {
                return _return(controller->createDtoResponse(status, message));
            } else {
                return request->readBodyToDtoAsync<oatpp::Object<UserDto>>(
                        controller->getDefaultObjectMapper()).callbackTo(&CreateUser::returnResponse);
            }
        }

        Action returnResponse(const oatpp::Object<UserDto> &body) {
            OATPP_COMPONENT(std::shared_ptr<koloboot::db::Database>, database);
            if (database->usernameIsExists(body->username->c_str())) {
                oatpp::Object<MessageDto> msg_dto = MessageDto::createShared();
                msg_dto->message = "Username telah terdaftar";
                return _return(controller->createDtoResponse(Status::CODE_200, msg_dto));
            } else {
                const std::string pass = sha256(body->password->c_str());
                body->password = pass.c_str();
                return _return(controller->createDtoResponse(Status::CODE_200, database->createUser(body)));
            }
        }
    };

    ENDPOINT_ASYNC("POST", "/api/user/login", LoginUser) {
    ENDPOINT_ASYNC_INIT(LoginUser)

        Action act() override {
            oatpp::Object<MessageDto> message = MessageDto::createShared();
            Status status = Status::CODE_200;
            verifikasiRequest(request, [&message, &status](oatpp::Object<MessageDto> m, Status stat) {
                message = m;
                status = stat;
            }, VerifContent::type);
            if (message != nullptr) {
                return _return(controller->createDtoResponse(status, message));
            } else {
                return request->readBodyToDtoAsync<oatpp::Object<UserDto>>(
                        controller->getDefaultObjectMapper()).callbackTo(&LoginUser::returnResponse);
            }
        }

        Action returnResponse(const oatpp::Object<UserDto> &body) {
            OATPP_COMPONENT(std::shared_ptr<koloboot::db::Database>, database);
            auto res = database->login(body);
            oatpp::Object<MessageDto> message = MessageDto::createShared();
            if (res) {
                message->message = "OK";
                message->data = res;
                message->code = 200;
            }
            else {
                message->message = "NO";
                message->data = nullptr;
                message->code = 200;
            }
            return _return(controller->createDtoResponse(Status::CODE_200, message));
        }
    };

    ENDPOINT_ASYNC("POST", "/api/muhsinin/create", CreateMuhsinin) {
    ENDPOINT_ASYNC_INIT(CreateMuhsinin)

        Action act() override {
            oatpp::Object<MessageDto> message = nullptr;
            Status status = Status::CODE_200;
            verifikasiRequest(request, [&message, &status](oatpp::Object<MessageDto> m, Status stat) {
                message = m;
                status = stat;
            }, VerifAuth::type);

            if (message != nullptr) {
                return _return(controller->createDtoResponse(status, message));
            } else {
                return request->readBodyToDtoAsync<oatpp::Object<DonaturDto>>(
                        controller->getDefaultObjectMapper()).callbackTo(&CreateMuhsinin::returnResponse);
            }
        }

        Action returnResponse(const oatpp::Object<DonaturDto> &body) {
            OATPP_COMPONENT(std::shared_ptr<koloboot::db::Database>, database);
            oatpp::Object<MessageDto> message = MessageDto::createShared();
            message->code = 200;
            message->message = "OK";
            auto res = database->createDonatur(body);
            message->data = res;
            return _return(controller->createDtoResponse(Status::CODE_200, message));
        }
    };

    ENDPOINT_ASYNC("DELETE", "/api/muhsinin/delete", DeleteMuhsinin) {
    ENDPOINT_ASYNC_INIT(DeleteMuhsinin)

        Action act() override {
            oatpp::Object<MessageDto> message = nullptr;
            Status status = Status::CODE_200;
            verifikasiRequest(request, [&message, &status](oatpp::Object<MessageDto> m, Status stat) {
                message = m;
                status = stat;
            }, VerifAuth::type);

            if (message != nullptr) {
                return _return(controller->createDtoResponse(status, message));
            } else {
                return request->readBodyToDtoAsync<oatpp::Object<DonaturDto>>(
                        controller->getDefaultObjectMapper()).callbackTo(&DeleteMuhsinin::returnResponse);
            }
        }

        Action returnResponse(const oatpp::Object<DonaturDto> &body) {
            OATPP_COMPONENT(std::shared_ptr<koloboot::db::Database>, database);
            oatpp::Object<MessageDto> message = MessageDto::createShared();
            message->code = 200;
            bool res = database->deleteDonatur(body->alias->c_str());
            if (res) {
                message->message = "OK";
            } else
                message->message = "NO";
            message->data = nullptr;
            return _return(controller->createDtoResponse(Status::CODE_200, message));
        }
    };

    ENDPOINT_ASYNC("POST", "/api/rekap/create", CreateRekap) {
    ENDPOINT_ASYNC_INIT(CreateRekap)

        Action act() override {
            oatpp::Object<MessageDto> message = nullptr;
            Status status = Status::CODE_200;
            verifikasiRequest(request, [&message, &status](oatpp::Object<MessageDto> m, Status stat) {
                message = m;
                status = stat;
            }, VerifAuth::type);

            if (message != nullptr) {
                return _return(controller->createDtoResponse(status, message));
            } else {
                return request->readBodyToDtoAsync<oatpp::Object<RekapDto>>(
                        controller->getDefaultObjectMapper()).callbackTo(&CreateRekap::returnResponse);
            }
        }

        Action returnResponse(const oatpp::Object<RekapDto> &body) {
            OATPP_COMPONENT(std::shared_ptr<koloboot::db::Database>, database);
            oatpp::Object<MessageDto> message = MessageDto::createShared();
            message->code = 200;
            oatpp::Object<RekapDto> result = nullptr;
            if (database->rekapIsExists(body) == true) {
                result = database->updateRekap(body);
                message->message = "OK";
            } else {
                result = database->createRekap(body);
                message->message = "OK";
            }
            message->data = result;
            return _return(controller->createDtoResponse(Status::CODE_200, message));
        }
    };

    ENDPOINT_ASYNC("PUT", "/api/rekap/update", UpdateRekap) {
        ENDPOINT_ASYNC_INIT(UpdateRekap)

        Action act() override {
            oatpp::Object<MessageDto> message = nullptr;
            Status status = Status::CODE_200;
            verifikasiRequest(request, [&message, &status](oatpp::Object<MessageDto> m, Status stat){
                message = m;
                status = stat;
            }, VerifAuth::type);

            if (message != nullptr) {
                return _return(controller->createDtoResponse(status, message));
            }
            else {
                return request->readBodyToDtoAsync<oatpp::Object<RekapDto>>(controller->getDefaultObjectMapper()).callbackTo(&UpdateRekap::returnResponse);
            }
        }

        Action returnResponse(const oatpp::Object<RekapDto>& body) {
            OATPP_COMPONENT(std::shared_ptr<koloboot::db::Database>, database);
            oatpp::Object<MessageDto> message = MessageDto::createShared();
            message->code = 200;
            oatpp::Object<RekapDto> result = nullptr;
            if (database->rekapIsExists(body) == true) {
                result = database->updateRekap(body);
                message->message = "OK";
            }
            else {
                message->message = "NO";
            }
            message->data = result;
            return _return(controller->createDtoResponse(Status::CODE_200, message));
        }
    };

    ENDPOINT_ASYNC("DELETE", "/api/rekap/delete", DeleteRekap) {
        ENDPOINT_ASYNC_INIT(DeleteRekap)

        Action act() override {
            oatpp::Object<MessageDto> message = nullptr;
            Status status = Status::CODE_200;
            verifikasiRequest(request, [&message, &status](oatpp::Object<MessageDto> m, Status stat){
                message = m;
                status = stat;
            }, VerifAuth::type);

            if (message != nullptr) {
                return _return(controller->createDtoResponse(status, message));
            }
            else {
                return request->readBodyToDtoAsync<oatpp::Object<RekapDto>>(controller->getDefaultObjectMapper()).callbackTo(&DeleteRekap::returnResponse);
            }
        }

        Action returnResponse(const oatpp::Object<RekapDto>& body) {
            OATPP_COMPONENT(std::shared_ptr<koloboot::db::Database>, database);
            oatpp::Object<MessageDto> message = MessageDto::createShared();
            message->code = 200;
            if (database->deleteRekap(body->kode->c_str()) == true) {
                message->message = "OK";
            }
            else {
                message->message = "NO";
            }
            return _return(controller->createDtoResponse(Status::CODE_200, message));
        }
    };
};

#include OATPP_CODEGEN_BEGIN(ApiController)

#endif // MYCONTROLLER_HPP
