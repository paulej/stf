# Simple Test Framework

## Purpose

The Simple Test Framework (STF) makes unit testing C++ code a snap, and
does so with an extremely small footprint.

## Usage

The Simple Test Framework consists of just one header file and one
implementation file that includes a `main()` function that will invoke all
registered unit tests.  It is purposely very simple, making it very easy to
create unit test code that has a consistent look and feel.  Just include the
`stf.h` header file at the top of the unit test code and define test functions
like this:

```cpp
#include <stf/stf.h>

STF_TEST(GroupName, MyTest1)
{
    // Perform some kind of operations
    int a = 1;
    int b = 1;

    // Verify results
    STF_ASSERT_EQ(a, b);
}
```

The first parameter is the name of a group of tests and used only to make it
easier to understand what tests are running, especially when there are multiple
test groups having tests with the same or similar name.  The second parameter
is the name of the test.  Test names within a test group must be unique, but
test names may be the same across different groups.

The test directory of the STF repository provides examples of how to construct
unit test files.  As demonstrated by the tests in test/dissimilar_types, it is
possible to have multiple compilation units with different test groups in the
same test module.

Tests, by default, are allowed to run for up to `Default_Timeout` seconds.
If more or less time is desired, an alternative to the above macro includes a
timeout parameters that indicates the maximum time in seconds:

```cpp
STF_TEST_TIMEOUT(GroupName, MyTest, Timeout)
```

A `main()` function is defined in `stf.cpp`.  Tests are automatically registered
via the `STF_TEST()` macro.  A test module is a file that includes the code to
be tested, the `stf.h` header file, and test code that uses the STF-related
macros like the example above linked with the STF library.  The complete set of
macros used for testing are:

```cpp
STF_TEST(GroupName, TestName)       // Define a test function
STF_TEST_TIMEOUT(Grp, Tst, Time)    // Define a test function with timeout
STF_TEST_EXCLUDE(Group, Test)       // Specify a test to exclude
STF_ASSERT_EQ(expected, actual)     // Assert expected == actual
STF_ASSERT_NE(a, b)                 // Assert a != b
STF_ASSERT_GT(a, b)                 // Assert a > b
STF_ASSERT_GE(a, b)                 // Assert a >= b
STF_ASSERT_LT(a, b)                 // Assert a < b
STF_ASSERT_LE(a, b)                 // Assert a <= b
STF_ASSERT_TRUE(a)                  // Assert a is true
STF_ASSERT_FALSE(a)                 // Assert a is false
STF_ASSERT_CLOSE(a, b, epsilon)     // Assert abs(a - b) < epsilon
STF_ASSERT_MEM_EQ(a, b, octets)     // Compare equal memory ranges
STF_ASSERT_MEM_NE(a, b, octets)     // Compare non-equal memory ranges
STF_ASSERT_EXCEPTION(f)             // Assert f throws any exception
STF_ASSERT_EXCEPTION_E(f, e)        // Assert f throws exception e
```

When performing comparisons of user-defined types, it is important that
comparison operators are defined for those types.  Further, if the
comparison fails, this test framework will attempt to output the type
to `std::cout`.  If a user-defined type does not have a streaming operator
defined, the library will indicate the object is unprintable when
a test fails.  One may define a streaming operator before including
this header file so that the library is aware of the operator's
existence.  See the [Adapters](#adapters) section below for more detail.

To test if a function call throws an exception, one passes the name of
the function to call in the macro.  The macro excepts a type of
`std::function<void()>`.  While one can pass a std::function object, the
simplest way to test exceptions is by doing the following:

```cpp
auto test_func = [&] { SomeFunction(arg1, arg2); }
STF_ASSERT_EXCEPTION(test_func)
```

Alternatively, the lambda may be inserted directly as shown:

```cpp
STF_ASSERT_EXCEPTION([&] { SomeFunction(arg1, arg2); })
```

When testing for an explicit exception to be thrown, it is important
that the exception type `e` be as specific as possible.  For example,
if one passes `std::exception` as the exception parameter, anything
thrown that is derived from `std::exception` (e.g., `std::runtime_error`)
would pass the test.  Tests should specify the exact exception type
expected.

The `STF_TEST_EXCLUDE` macro specifies which tests should be excludes
from test runs.  This is useful if there is a known failing test that
needs to be excluded temporarily or when there are some tests that need
to be performed only under certain conditions that can be articulated
at compile time.

## Adapters

When assertions fail, STF will attempt to print the objects using a streaming
operator.  If there is no streaming operator defined for a given object,
the assertion failure will be reported similarly to this:

```text
Assertion failed at /path/to/binary:<line>
  expected: [Unprintable object at address 0x0x7efda6d3fcb0]
    actual: [Unprintable object at address 0x0x7efda6d3fc90]
```

One may define a streaming operator for the unprintable object.  In the
`stf/adapters` include directory, there are pre-defined streaming adapters
for common types, like integrals arrays and vectors.  To use those,
include the adapter header files _before_ including `stf/stf.h`.

For example, one should do this if it is desired to produce a hex dump of
integral arrays:

```cpp
#include <stf/adapters/integral_array.h>
#include <stf/stf.h>
```

When creating one's own adapter, the function prototype must be declared
before including `stf/stf.h`.  The implementation may be provided anywhere,
as long as the linker is able to find it.  For example, this would be a valid
approach:

```cpp
// Declare the streaming operator for MyOject before including stf/stf.h
std::ostream &operator<<(std::ostream &, const MyObject &);

// Include STF
#include <stf/stf.h>

// One may then define the streaming operator later for MyObject
```

## Examples

The STF library includes unit tests for itself that serve as good examples
of how to use the framework.  See the directory `test` for those examples.

## Including STF in Projects

### Using CMake

If STF is already installed on the system, one can use `find_package(stf)`
in order to locate it.  This will make the library and required header
file `stf.h` visible to the test code when linking with `STF::stf`.

If not installed or if it's preferred to fetch the code, one may use
`FetchContent` to download the code directly via the repository.

A CMake recipe one might use is this:

```cmake
include(FetchContent)

# Try to find the installed STF package
find_package(stf QUIET)

# If STF is not found, fetch the source code from the repository
if(NOT stf_FOUND)
    # Set the desired C++ version to test; 20 is the current default
    set(stf_CPP_STD 20 CACHE STRING "C++ Version for Testing with STF")

    FetchContent_Declare(stf
        GIT_REPOSITORY https://github.com/paulej/stf.git
        GIT_TAG        master
        GIT_SHALLOW    true)
    FetchContent_MakeAvailable(stf)
endif()
```

The above code checks to see if STF is already installed and, if so, take
no further action.  The `find_package()` function will ensure dependencies
get satisfied in any subdirectories.  If the STF library was not found, the
source code will be fetched from the repository and built when the project
is built.

Linking to the library and making the header file visible to test code
is accomplished with a line like this:

```cmake
target_link_libraries(<TARGET> STF::stf)
```

Here, `<TARGET>` is the test module to build.  See the `test` directory for
several examples.

### Using Other Build Systems

If using `make`, Visual Studio, or other build system to compile test code,
first build the STF library.  Once the `.a` or `.lib` file is created,
just link that library with the test code you are trying to build.  You will
also need to ensure that the include paths are properly set so that `stf.h`
can be found.
