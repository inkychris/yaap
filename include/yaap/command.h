#ifndef YAAP_COMMAND_H
#define YAAP_COMMAND_H

#include "yaap/argument.h"
#include "yaap/flag.h"
#include "yaap/util.h"

namespace yaap {

    class Command {
    public:
        typedef std::shared_ptr<Command> ptr;

        explicit Command(std::string id);

        void execute(string_vector);

        void add_flag(Flag::ptr flag);
        void add_flag(const std::string& id, bool& target);
        void add_flag(const std::string& id, bool& target, std::string help_message);

        run_function run;

    private:
        std::string _id;
        std::vector<Command> _sub_commands;
        std::vector<Processable::ptr> _positional_args;
        std::vector<Processable::ptr> _optional_named_args;
        std::vector<Processable::ptr> _required_named_args;
        std::vector<Processable::ptr> _flag_args;
    };
}

#endif
