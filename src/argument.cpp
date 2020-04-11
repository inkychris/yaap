#include <sstream>
#include "yaap/yaap.h"

yaap::Argument::Argument(const std::string& id, std::string help_message) :
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
};
