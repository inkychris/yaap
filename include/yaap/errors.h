#ifndef YAAP_ERRORS_H
#define YAAP_ERRORS_H

namespace yaap {
    typedef std::exception Error;

    class UnhandledArgumentsError : Error {
    public:
        explicit UnhandledArgumentsError(const arglist& args) {
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
