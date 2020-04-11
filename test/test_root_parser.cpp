#define CATCH_CONFIG_MAIN
#include <functional>

#include <catch2/catch.hpp>
#include "yaap/yaap.h"
#include "yaap/errors.h"

struct Args {
    std::string arg1;
    bool verbose;
    int port;
};

Args parsed_args = {};

std::function<void()> test(const std::string& arg1, bool verbose, int port) {
    return [arg1, verbose, port]() {
        REQUIRE(parsed_args.arg1 == arg1);
        REQUIRE(parsed_args.verbose == verbose);
        REQUIRE(parsed_args.port == port);
    };
}

TEST_CASE("single flag", "[yaap:root parser]") {
    auto cmd = yaap::Command("test");

    cmd.add_flag("v|verbose", parsed_args.verbose);

    SECTION("no args provided") {
        cmd.run = test("", false, 0);
        cmd.execute({});
    }

    SECTION("long flag") {
        cmd.run = test("", true, 0);
        cmd.execute({"--verbose"});
    }

    SECTION("short flag") {
        cmd.run = test("", true, 0);
        cmd.execute({"-v"});
    }

    SECTION("single unknown arg") {
        REQUIRE_THROWS_AS(cmd.execute({"extra"}), yaap::UnhandledArgumentsError);
    }

    SECTION("unknown arg with known flag") {
        REQUIRE_THROWS_AS(cmd.execute({"--verbose", "extra"}), yaap::UnhandledArgumentsError);
    }
}
