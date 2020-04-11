#include <utility>
#include "yaap/yaap.h"

yaap::Flag::Flag(const std::string& id, bool& target) :
    Argument(id, ""),
    _target(&target) {}

yaap::Flag::Flag(const std::string& id, bool& target, std::string help_message) :
    Argument(id, std::move(help_message)),
    _target(&target) {}

yaap::string_vector yaap::Flag::process(string_vector args) {
    for (const auto& arg : args) {
        for (const auto& long_id : _long_ids) {
            if (arg == "--" + long_id) {
                *_target = true;
                args.erase(std::remove(args.begin(), args.end(), arg), args.end());
                return args;
            }
        }
        for (const auto& short_id : _short_ids) {
            if (arg == "-" + short_id) {
                *_target = true;
                args.erase(std::remove(args.begin(), args.end(), arg), args.end());
                return args;
            }
        }
    }
    return args;
}
