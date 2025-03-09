#include <CLI/CLI.hpp>
#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <toml++/toml.hpp>

#include <archive.h>
#include <archive_entry.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------------------------------------------------------------

void create_archive(const char *archive_name) {
    struct archive *a;
    struct archive_entry *entry;
    char buff[8192];
    int len;

    // Create a new archive object
    a = archive_write_new();
    archive_write_set_format_pax_restricted(a); // Set tar format
    archive_write_open_filename(a, archive_name); // Open archive for writing

    // Create a new entry
    entry = archive_entry_new();
    archive_entry_set_pathname(entry, "example.txt");
    archive_entry_set_size(entry, 13); // File size
    archive_entry_set_filetype(entry, AE_IFREG); // Regular file
    archive_entry_set_perm(entry, 0644); // Permissions

    // Write header
    archive_write_header(a, entry);

    // Write file data
    strcpy(buff, "Hello, world");
    archive_write_data(a, buff, strlen(buff));

    // Finish entry
    archive_entry_free(entry);

    // Close archive
    archive_write_close(a);
    archive_write_free(a);

    printf("Archive %s created successfully.\n", archive_name);
}


int main(int argc, char **argv)
{
    CLI::App app{"App description"};
    argv = app.ensure_utf8(argv);

    std::string filename = "default";
    app.add_option("-f,--file", filename, "A help string");

    CLI11_PARSE(app, argc, argv);

    create_archive("output.tar");

    return 0;
}
//---------------------------------------------------------------------------
