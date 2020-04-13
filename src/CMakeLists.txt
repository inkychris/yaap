add_library(yaap
    command.cpp
    flag.cpp
    ../include/yaap/yaap.h
    ../include/yaap/errors.h
)
target_include_directories(yaap PUBLIC ../include)
target_compile_features(yaap PUBLIC cxx_std_11)

target_compile_options(yaap PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>
)
