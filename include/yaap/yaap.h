#ifndef YAAP_YAAP_H
#define YAAP_YAAP_H

#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <functional>

namespace yaap {
    typedef std::vector<std::string> string_vector;
    typedef std::function<void()> run_function;

    class Processable {
    public:
        typedef std::shared_ptr<Processable> ptr;
        virtual string_vector process(string_vector args) = 0;
    };

    template <typename target_t>
    class Argument : public Processable {
    public:
        typedef std::shared_ptr<Argument> ptr;

        Argument(const std::string& id, target_t& target);
        Argument(const std::string& id, target_t& target, std::string help_message);

    protected:
        string_vector _long_ids;
        string_vector _short_ids;
        target_t* _target;
    private:
        std::string _help_message;
    };

    class Flag : public Argument<bool> {
    public:
        Flag(const std::string& id, bool& target) : Argument(id, target) {};

        Flag(const std::string& id, bool& target, std::string help_message) :
            Argument(id, target, std::move(help_message)) {};

        string_vector process(string_vector args) override;
    };

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

template <typename target_t>
yaap::Argument<target_t>::Argument(const std::string& id, target_t& target, std::string help_message) :
        _target(&target),
        _help_message(std::move(help_message))
{
    std::string current_id;
    std::istringstream id_stream {id};
    while(std::getline(id_stream, current_id, '|')){
        if (current_id.size() == 1)
            _short_ids.push_back(current_id);
        else
            _long_ids.push_back(current_id);
    }
}

template <typename target_t>
yaap::Argument<target_t>::Argument(const std::string& id, target_t& target) : Argument(id, target, "") {}

#endif
