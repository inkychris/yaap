#ifndef YAAP_YAAP_H
#define YAAP_YAAP_H

#include <string>
#include <vector>
#include <functional>

namespace yaap {
    typedef std::vector<std::string> string_vector;
    typedef std::function<void()> run_function;


    class Argument {
    public:
        explicit Argument(const std::string& id, std::string help_message);
        virtual string_vector process(string_vector args) = 0;

    protected:
        string_vector _long_ids;
        string_vector _short_ids;
    private:
        std::string _help_message;
    };


    class Flag : public Argument {
    public:
        Flag(const std::string& id, bool& target);
        Flag(const std::string& id, bool& target, std::string help_message);

        string_vector process(string_vector args) override;

    private:
        bool* _target;
    };


    class Command {
    public:
        explicit Command(std::string id);

        void execute(string_vector);

        void add_flag(const std::string& id, bool& target);
        void add_flag(const std::string& id, bool& target, std::string help_message);

        run_function run;

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
