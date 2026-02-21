cmake_minimum_required(VERSION 3.20)

# vcpkg toolchain (замени на свой реальный путь, если не в manifest-режиме)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE FILEPATH "vcpkg toolchain")

project(mini-search-engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Отдельные find_package для каждого Boost-модуля (как требует vcpkg для modular Boost)
find_package(boost_beast CONFIG REQUIRED)
find_package(boost_asio CONFIG REQUIRED)
find_package(boost_property_tree CONFIG REQUIRED)
find_package(boost_locale CONFIG REQUIRED)

find_package(libpqxx CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

find_path(GUMBO_INCLUDE_DIR gumbo.h)
find_library(GUMBO_LIBRARY gumbo)

add_executable(spider
    src/main.cpp
    src/config.cpp
    src/database.cpp
    src/http_client.cpp
    src/HTML_parser.cpp
)

if (GUMBO_INCLUDE_DIR AND GUMBO_LIBRARY)
    message(STATUS "Found Gumbo: ${GUMBO_LIBRARY}")
    target_include_directories(spider PRIVATE ${GUMBO_INCLUDE_DIR})
    target_link_libraries(spider PRIVATE ${GUMBO_LIBRARY})
else()
    message(FATAL_ERROR "Gumbo not found. Make sure 'gumbo' is installed via vcpkg.")
endif()

target_link_libraries(spider PRIVATE
    Boost::beast
    Boost::asio
    Boost::property_tree
    Boost::locale
    libpqxx::pqxx
    pugixml
    OpenSSL::SSL
    OpenSSL::Crypto
)