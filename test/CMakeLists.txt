add_executable(test_yaap test_root_parser.cpp)
target_compile_features(test_yaap PRIVATE cxx_std_11)
target_link_libraries(test_yaap PRIVATE Catch2::Catch2 yaap)
add_test(NAME test_yaap COMMAND test_yaap)
