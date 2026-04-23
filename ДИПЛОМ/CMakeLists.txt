cmake_minimum_required(VERSION 3.20)
project(SearchEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#важно для visual Studio, надо разместить exe прямо в корне проекта для удобства запуска программы

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR})

option(BUILD_INDEXER "Build indexer" ON)
option(BUILD_SEARCHER "Build searcher" ON)

find_package(Threads REQUIRED)

set(COMMON_SOURCES
    src/config.cpp
    src/text_processor.cpp
    src/db_manager.cpp
	src/thread_pool.cpp
)

if(BUILD_INDEXER)
    add_executable(indexer
        src/indexer.cpp
        ${COMMON_SOURCES}
    )
    target_link_libraries(indexer PRIVATE Threads::Threads)
    target_include_directories(indexer PRIVATE src)
endif()

if(BUILD_SEARCHER)
    add_executable(searcher
        src/searcher.cpp
        ${COMMON_SOURCES}
    )
    target_link_libraries(searcher PRIVATE Threads::Threads)
    target_include_directories(searcher PRIVATE src)
endif()

message(STATUS "Project configured with C++20")
message(STATUS "Executables will be placed directly in project ROOT")