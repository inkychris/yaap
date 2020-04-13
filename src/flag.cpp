#include <algorithm>
#include "yaap/flag.h"

bool string_startswith(const std::string& string, const std::string& prefix) {
    if (string.size() < prefix.size())
        return false;
    for (int index = 0; index < prefix.size(); index++) {
        if (string[index] != prefix[index])
            return false;
    }
    return true;
}

yaap::string_vector yaap::Flag::process(string_vector args) {
    for (auto& arg : args) {
        if (!string_startswith(arg, "-"))
            continue;

        if (string_startswith(arg, "--")) {
            for (const auto &long_id : _long_ids) {
                if (arg == "--" + long_id) {
                    *_target = true;
                    args.erase(std::remove(args.begin(), args.end(), arg), args.end());
                    return args;
                }
            }
        }

        for (const auto& short_id : _short_ids) {
            if (arg == '-' + short_id) {
                *_target = true;
                args.erase(std::remove(args.begin(), args.end(), arg), args.end());
                return args;
            }

            if ((arg.size() >= 2) && (arg.find(short_id) != std::string::npos)) {
                std::string modified_arg;
                for (auto element : arg)
                    if (element != short_id[0])
                        modified_arg.push_back(element);
                arg = modified_arg;
                return args;
            }
        }
    }
    return args;
}
