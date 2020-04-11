#ifndef YAAP_YAAP_H
#define YAAP_YAAP_H

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <exception>

namespace yaap {
    typedef std::vector<std::string> arglist;
    typedef std::function<void()> run_function;


    class Argument {
    public:
        explicit Argument(std::string id) : _id(std::move(id)) {};
        virtual arglist process(arglist args) = 0;
    protected:
        std::string _id;
    };


    class Flag : public Argument {
    public:
        Flag(std::string id, bool& target);

        arglist process(arglist args) override;

    private:
        bool* _target;
    };


    class Command {
    public:
        explicit Command(std::string id);

        void execute(arglist);

        void add_flag(Flag&);

        run_function run;
        std::string help_message;

    private:
        std::string _id;
        std::vector<Command> _sub_commands;
        std::vector<Argument> _positional_args;
        std::vector<Argument> _optional_named_args;
        std::vector<Argument> _required_named_args;
        std::vector<Flag> _flag_args;
    };
}

#endif
