#include <utility>
#include "yaap/yaap.h"
#include "yaap/errors.h"

yaap::Command::Command(std::string id) : _id(std::move(id)) {};

void yaap::Command::execute(arglist args) {
    for (auto entry : _flag_args) {
        args = entry.process(args);
    }
    if (!args.empty())
        throw yaap::UnhandledArgumentsError(args);
    run();
}

void yaap::Command::add_flag(Flag& argument) {
    _flag_args.push_back(argument);
}
