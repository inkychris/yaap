add_library(yaap
    argument.cpp
    command.cpp
    flag.cpp
    ../include/yaap/yaap.h
    ../include/yaap/errors.h
)
target_include_directories(yaap PUBLIC ../include)
target_compile_features(yaap PUBLIC cxx_std_11)
