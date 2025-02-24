#include <iostream>
#include <spdlog/spdlog.h>
#include <fmt/core.h>
#include <toml++/toml.hpp>

using namespace std::literals;

int main()
{
    spdlog::info("Hello, this is spdlog!");
    std::cout << fmt::format("Formatted output: {}\n", 42);
	
	// Create a TOML document from a string
    const char* toml_data = R"(
        title = "TOML Example"
        owner = { name = "Tom Preston-Werner", dob = 1979-05-27 }
        database = { server = "192.0.2.0", ports = [ 8001, 8001, 8002 ], connection_max = 5000, enabled = true }
    )";


    auto config = toml::parse_file( "configuration.toml" );

    // get key-value pairs
    std::string_view library_name = config["library"]["name"].value_or(""sv);
    std::string_view library_author = config["library"]["authors"][0].value_or(""sv);
    int64_t depends_on_cpp_version = config["dependencies"]["cpp"].value_or(0);

    // modify the data
    config.insert_or_assign("alternatives", toml::array{
        "cpptoml",
        "toml11",
        "Boost.TOML"
    });

    return 0;
}
