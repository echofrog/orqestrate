cmake_minimum_required(VERSION 3.24)
project(orqestrate CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)
set(FTXUI_LIB_DIR "${CMAKE_BINARY_DIR}/_deps/ftxui-build/Debug")

FetchContent_Declare(
    libarchive
    GIT_REPOSITORY https://github.com/libarchive/libarchive.git
    GIT_TAG v3.6.2
)
FetchContent_MakeAvailable(libarchive)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.10.0
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)

add_executable(orqestrate src/main.cpp)

target_link_libraries(orqestrate PRIVATE
	archive
	fmt
    ${FTXUI_LIB_DIR}/ftxui-component.lib
    ${FTXUI_LIB_DIR}/ftxui-dom.lib
    ${FTXUI_LIB_DIR}/ftxui-screen.lib
	spdlog::spdlog
)

target_include_directories(
	orqestrate PRIVATE ${CMAKE_SOURCE_DIR}/src
	${CMAKE_BINARY_DIR}/_deps/tomlplusplus-src/include
)
