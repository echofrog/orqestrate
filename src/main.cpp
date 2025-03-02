#include <iostream>
#include <spdlog/spdlog.h>
#include <fmt/core.h>
#include <toml++/toml.hpp>

using namespace std::literals;

int main()
{
    spdlog::error("This is an error log.");

    std::cout << fmt::format("Formatted output: {}\n", 42);
	
	// Create a TOML document from a string
    const char* toml_data = R"(
        title = "TOML Example"
        owner = { name = "Tom Preston-Werner", dob = 1979-05-27 }
        database = { server = "192.0.2.0", ports = [ 8001, 8001, 8002 ], connection_max = 5000, enabled = true }
    )";

    spdlog::info("Welcome to spdlog");

    return 0;
}
