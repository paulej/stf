# Specify the test to build
add_executable(test_miscellaneous test_miscellaneous.cpp)

# Link the executable with STF
target_link_libraries(test_miscellaneous STF::stf)

# Specify the C++ standard to observe
set_target_properties(test_miscellaneous
    PROPERTIES
        CXX_STANDARD ${stf_CPP_STD}
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

# Use the following compile options
target_compile_options(test_miscellaneous
    PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Wpedantic -Wextra -Wall>
        $<$<CXX_COMPILER_ID:MSVC>: >)

# Add the test so that CTest can invoke it
add_test(NAME test_miscellaneous
         COMMAND test_miscellaneous)
