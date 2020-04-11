#include "yaap/yaap.h"

yaap::Flag::Flag(std::string id, bool& target) : Argument(std::move(id)), _target(&target) {}

yaap::arglist yaap::Flag::process(arglist args) {
    for (const auto& arg : args) {
        if (arg == "--" + _id) {
            *_target = true;
            args.erase(std::remove(args.begin(), args.end(), arg), args.end());
            return args;
        }
    }
    return args;
}
