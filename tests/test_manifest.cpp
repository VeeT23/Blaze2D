#include <catch2/catch_test_macros.hpp>
#include <Blaze2D/util/Manifest.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <chrono>

static std::filesystem::path write_temp_manifest(const std::string& contents)
{
    using namespace std::chrono;
    auto dir = std::filesystem::temp_directory_path();
    auto name = "blaze_manifest_test_" + std::to_string(duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count()) + ".manifest";
    auto path = dir / name;

    std::ofstream ofs(path, std::ios::binary);
    ofs << contents;
    ofs.close();

    return path;
}

TEST_CASE("Manifest loads valid manifest and provides accessors", "[manifest]")
{
    const std::string manifestContents = R"(# Example manifest
sprite | hero | assets/hero.png | FLAG | KEY = VALUE | BOOLEAN_FLAG = true

audio | music | assets/music.mp3

-----
sprite | enemy | assets/enemy.png | SPEED = 10
)";

    auto path = write_temp_manifest(manifestContents);
    REQUIRE(std::filesystem::exists(path));

    blaze::Manifest manifest(path);

    // getAll should report 3 assets
    auto all = manifest.getAll();
    REQUIRE(all.size() == 3);

    // get() for an existing asset
    const auto& hero = manifest.get("hero");
    REQUIRE(hero.name == "hero");
    REQUIRE(hero.type == "sprite");
    REQUIRE(hero.path == std::filesystem::path("assets/hero.png"));
    REQUIRE(hero.flags.at("FLAG") == "true");
    REQUIRE(hero.flags.at("KEY") == "VALUE");
    REQUIRE(hero.flags.at("BOOLEAN_FLAG") == "true");

    // get() throws for missing asset
    REQUIRE_THROWS_AS(manifest.get("does_not_exist"), std::out_of_range);

    // getByType should report number of assets of a given type.
    // Note: getByType returns a span; verify size matches expected count.
    auto sprites = manifest.getByType("sprite");
    REQUIRE(sprites.size() == 2);

    // Verify that the manifest contains the expected names for the 'sprite' type
    bool foundHero = false;
    bool foundEnemy = false;
    for (const auto& a : manifest.getAll()) {
        if (a.type == "sprite") {
            if (a.name == "hero") foundHero = true;
            if (a.name == "enemy") foundEnemy = true;
        }
    }
    REQUIRE(foundHero);
    REQUIRE(foundEnemy);

    std::filesystem::remove(path);
}

TEST_CASE("Manifest constructor throws when manifest file does not exist", "[manifest]")
{
    auto tmp = std::filesystem::temp_directory_path() / "nonexistent_manifest_file_for_test_123456789.manifest";
    REQUIRE_FALSE(std::filesystem::exists(tmp));
    REQUIRE_THROWS_AS(blaze::Manifest(tmp), std::runtime_error);
}

TEST_CASE("Manifest constructor throws on duplicate asset names", "[manifest]")
{
    const std::string manifestContents = R"(
sprite | dup | a.png
sprite | dup | b.png
)";

    auto path = write_temp_manifest(manifestContents);
    REQUIRE(std::filesystem::exists(path));

    REQUIRE_THROWS_AS(blaze::Manifest(path), std::runtime_error);

    std::filesystem::remove(path);
}

TEST_CASE("Manifest constructor throws on malformed manifest line", "[manifest]")
{
    // Line with fewer than three '|' segments should be considered malformed
    const std::string manifestContents = R"(
invalid_line_without_pipes
)";

    auto path = write_temp_manifest(manifestContents);
    REQUIRE(std::filesystem::exists(path));

    REQUIRE_THROWS_AS(blaze::Manifest(path), std::runtime_error);

    std::filesystem::remove(path);
}