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

add_executable(spider
    src/main.cpp
    src/config.cpp
    src/database.cpp
    src/http_client.cpp
)

target_link_libraries(spider PRIVATE
    Boost::beast
    Boost::asio
    Boost::property_tree
    Boost::locale
    libpqxx::pqxx
    pugixml
)