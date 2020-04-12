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

    cmd.add_flag("v|verbose|l|loud", parsed_args.verbose);

    SECTION("no args provided") {
        cmd.run = test("", false, 0);
        cmd.execute({});
    }

    yaap::string_vector valid_flags {"-v", "--verbose", "-l", "--loud"};
    SECTION("valid flags") {
        for (const auto& flag : valid_flags){
            SECTION(flag) {
                cmd.run = test("", true, 0);
                cmd.execute({flag});
            }
        }
    }

    SECTION("single unknown arg") {
        REQUIRE_THROWS_AS(cmd.execute({"extra"}), yaap::UnhandledArgumentsError);
    }

    SECTION("unknown arg with known flag") {
        REQUIRE_THROWS_AS(cmd.execute({"--verbose", "extra"}), yaap::UnhandledArgumentsError);
    }
}
