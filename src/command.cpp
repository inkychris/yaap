#include <memory>
#include <utility>
#include "yaap/yaap.h"
#include "yaap/errors.h"

yaap::Command::Command(std::string id) : _id(std::move(id)) {};

void yaap::Command::execute(string_vector args) {
    for (const auto& entry : _flag_args) {
        args = entry->process(args);
    }
    if (!args.empty())
        throw yaap::UnhandledArgumentsError(args);
    run();
}

void yaap::Command::add_flag(yaap::Flag::ptr flag) {
    _flag_args.push_back(std::move(flag));
}

void yaap::Command::add_flag(const std::string& id, bool& target) {
    add_flag(std::make_shared<yaap::Flag>(id, target));
}

void yaap::Command::add_flag(const std::string& id, bool& target, std::string help_message) {
    add_flag(std::make_shared<yaap::Flag>(id, target, std::move(help_message)));
}
