#ifndef YAAP_ARGUMENT_H
#define YAAP_ARGUMENT_H

#include <memory>
#include <sstream>
#include "yaap/util.h"

namespace yaap {
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
