#include <catch2/catch_test_macros.hpp>
#include <Blaze2D/Core.h>

TEST_CASE("Blaze2D initializes and shuts down cleanly")
{
    REQUIRE(blaze::Init() == true);

    // Calling shutdown twice should be safe
    blaze::Shutdown();
    blaze::Shutdown();
}
