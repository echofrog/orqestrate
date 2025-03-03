cmake_minimum_required(VERSION 3.24)
project(orqestrate CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
    add_definitions(-D_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING)
endif()

include(FetchContent)

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/third_party")

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
    archive
    GIT_REPOSITORY https://github.com/libarchive/libarchive.git
    GIT_TAG v3.6.2
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DPCRE=OFF -DPCREPOSIX=OFF
)
FetchContent_MakeAvailable(archive)

if(TARGET archive)
    set(ENABLE_TEST OFF CACHE BOOL "Disable tests for libarchive" FORCE)
    set(ENABLE_PCREPOSIX OFF CACHE BOOL "Disable PCREPOSIX for libarchive" FORCE)
    set(PCREPOSIX_FOUND FALSE CACHE BOOL "Override PCREPOSIX_FOUND to FALSE" FORCE)
    set(PCRE_FOUND FALSE CACHE BOOL "Override PCRE_FOUND to FALSE" FORCE)
endif()

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.10.0
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)

FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11
    GIT_TAG v2.5.0
)
FetchContent_MakeAvailable(CLI11)

add_executable(orqestrate src/main.cpp)

target_link_libraries(orqestrate PRIVATE
    archive
    CLI11
    fmt
    spdlog::spdlog
)

target_include_directories(orqestrate PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/third_party/tomlplusplus-src/include
)
