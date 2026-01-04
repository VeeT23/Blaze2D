#include <catch2/catch_test_macros.hpp>
#include <Blaze2D/App.h>

TEST_CASE("blaze::App creates windows correctly", "[App][Window]") {
    blaze::App app;

    SECTION("Default window size and title") {
        blaze::Window& test_1 = app.createWindow("Test 1");

        INFO("Checking window 1");
        CHECK(test_1.getWidth() == 100);
        CHECK(test_1.getHeight() == 100);
        CHECK(test_1.getName() == "Test 1");
        CHECK(test_1.getTitle() == "Test 1");
    }

    SECTION("Custom size with default title") {
        blaze::Window& test_2 = app.createWindow("Test 2", 500, 500);

        INFO("Checking window 2");
        CHECK(test_2.getWidth() == 500);
        CHECK(test_2.getHeight() == 500);
        CHECK(test_2.getName() == "Test 2");
        CHECK(test_2.getTitle() == "Test 2");
    }

    SECTION("Custom size and custom title") {
        blaze::Window& test_3 = app.createWindow("Test 3", 500, 500, "This is a test.");

        INFO("Checking window 3");
        CHECK(test_3.getWidth() == 500);
        CHECK(test_3.getHeight() == 500);
        CHECK(test_3.getName() == "Test 3");
        CHECK(test_3.getTitle() == "This is a test.");
    }
}

TEST_CASE("blaze::App gets windows correctly", "[App][Window]") {
    blaze::App app;
    blaze::Window& test = app.createWindow("Test");

    SECTION("Returns correct reference") {
        blaze::Window& result = app.getWindow("Test");
        CHECK(&test == &result);
    }
    
    SECTION("Fails if window doesn't exist") {
        REQUIRE_THROWS(app.getWindow("Fail"));
    }
}

TEST_CASE("blaze::App destroys windows correctly", "[App][Window]") {
   
    blaze::App app;
    blaze::Window& test = app.createWindow("Test");

    INFO("Ensuring window was made succesfully");
    REQUIRE_NOTHROW(app.getWindow("Test"));

    INFO("Ensuring removeWindow() calls without error");
    REQUIRE_NOTHROW(app.removeWindow(test));

    INFO("Ensuring window was deleted");
    REQUIRE_THROWS(app.getWindow("Test"));
}