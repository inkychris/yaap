#ifndef YAAP_ERRORS_H
#define YAAP_ERRORS_H

#include <exception>

namespace yaap {
    typedef std::exception Error;

    class UnhandledArgumentsError : public Error {
    public:
        explicit UnhandledArgumentsError(const string_vector& args) {
            _message = "unknown args: [";
            for (const auto& arg : args) {
                if (arg != args[0])
                    _message += ", ";
                _message += '"' + arg + '"';
            }
            _message += "]";
        }

        const char* what() const noexcept override {
            return _message.c_str();
        }

    private:
        std::string _message;
    };
}

#endif
