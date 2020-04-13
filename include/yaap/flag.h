#ifndef YAAP_FLAG_H
#define YAAP_FLAG_H

#include "yaap/util.h"
#include "yaap/argument.h"

namespace yaap {
    class Flag : public Argument<bool> {
    public:
        Flag(const std::string& id, bool& target) : Argument(id, target) {};

        Flag(const std::string& id, bool& target, std::string help_message) :
                Argument(id, target, std::move(help_message)) {};

        string_vector process(string_vector args) override;
    };
}

#endif
