#include <utility>
#include "yaap/yaap.h"
#include "yaap/errors.h"

yaap::Command::Command(std::string id) : _id(std::move(id)) {};

void yaap::Command::execute(string_vector args) {
    for (auto entry : _flag_args) {
        args = entry.process(args);
    }
    if (!args.empty())
        throw yaap::UnhandledArgumentsError(args);
    run();
}

void yaap::Command::add_flag(const std::string& id, bool& target) {
    _flag_args.emplace_back(id, target);
}

void yaap::Command::add_flag(const std::string& id, bool& target, std::string help_message) {
    _flag_args.emplace_back(id, target, std::move(help_message));
}
