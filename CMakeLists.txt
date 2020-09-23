cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME donasi-api)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME}-lib
    src/AppComponent.hpp
    src/db/basedb.hpp
    src/db/basedb.cpp
    src/db/database.hpp
    src/db/database.cpp
    src/dto/MyDTOs.hpp
    src/controller/mycontroller.hpp
    src/controller/mycontroller.cpp
    src/basecontroller.hpp
    src/basecontroller.cpp
    src/db/Model.hpp
    src/sha256.hpp
    src/sha256.cpp
)

find_package(mongocxx REQUIRED)

message("LIBBSONCXX_INCLUDE_DIRS=${LIBBSONCXX_INCLUDE_DIRS}")
message("LIBBSONCXX_LIBRARIES=${LIBBSONCXX_LIBRARIES}")

message("LIBMONGOCXX_INCLUDE_DIRS=${LIBMONGOCXX_INCLUDE_DIRS}")
message("LIBMONGOCXX_LIBRARIES=${LIBMONGOCXX_LIBRARIES}")

find_package(oatpp 1.1.0 REQUIRED)
find_package(oatpp-mongo 1.1.0 REQUIRED)

include_directories("${CMAKE_CURRENT_LIST_DIR}/third_party/jwt-cpp/")

find_package(OpenSSL REQUIRED)

message("LIBRARIES = ${LIBRARIES}")

target_link_libraries(${PROJECT_NAME}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-mongo
        PUBLIC oatpp::oatpp-test
        PUBLIC ${LIBRARIES}
        PUBLIC OpenSSL::Crypto
)

if (TARGET mongo::mongocxx_shared)
    target_link_libraries(${PROJECT_NAME}-lib
            PUBLIC mongo::mongocxx_shared
    )
    message("mongo::mongocxx_shared is used")
elseif(TARGET mongo::mongocxx_static)
    target_link_libraries(${PROJECT_NAME}-lib
            PUBLIC mongo::mongocxx_static
    )
endif()

target_include_directories(${PROJECT_NAME}-lib PUBLIC src)

add_executable(${PROJECT_NAME}-exe
        src/App.cpp
)
target_link_libraries(${PROJECT_NAME}-exe ${PROJECT_NAME}-lib)
add_dependencies(${PROJECT_NAME}-exe ${PROJECT_NAME}-lib)

add_executable(${PROJECT_NAME}-test
        test/tests.cpp
)
target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME}-lib)
add_dependencies(${PROJECT_NAME}-test ${PROJECT_NAME}-lib)

set_target_properties(${PROJECT_NAME}-lib ${PROJECT_NAME}-exe ${PROJECT_NAME}-test PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(project-tests ${PROJECT_NAME}-test)
