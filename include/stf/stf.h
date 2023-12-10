/*
 *  stf.h
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      This Simple Test Framework (STF) consists of just this one header file
 *      and one implementation file that includes a main() function that
 *      will invoke all registered unit tests.  It is purposely very simple,
 *      making it very easy to create unit test code that has a consistent look
 *      and feel.  Just include this header file at the top of the unit test
 *      code and define test functions like this:
 *
 *          #include <stf/stf.h>
 *
 *          STF_TEST(GroupName, MyTest1)
 *          {
 *              // Perform some kind of operations
 *              int a = 1;
 *              int b = 1;
 *
 *              // Verify equality
 *              STF_ASSERT_EQ(a, b);
 *          }
 *
 *      The first parameter is the name of a group of tests and used only
 *      to make it easier to understand what tests are running, especially
 *      when there are multiple test groups having tests with the same
 *      or similar name.  The second parameter is the name of the test.
 *      Test names within a test group must be unique, but test names may
 *      be the same across different groups.
 *
 *      The test directory of the STF repository provides examples of how
 *      to construct unit test files.  As demonstrated by the tests in
 *      test/dissimilar_types, it is possible to have multiple compilation
 *      units with different test groups in the same unit test module.
 *
 *      Tests, by default, are allowed to run for up to Default_Timeout
 *      seconds.  If more or less time is desired, an alternative to the
 *      above macro includes a timeout parameters that indicates the maximum
 *      time in seconds:
 *
 *          STF_TEST_TIMEOUT(GroupName, MyTest, Timeout)
 *
 *      A main() function is defined in stf.cpp.  Tests are automatically
 *      registered via the STF_TEST() macro.  A test module is a file that
 *      includes the code to be tested, the stf.h header file, and test code
 *      that uses the STF-related macros like the example above linked with
 *      the STF library.  The complete set of macros used for testing are:
 *
 *          STF_TEST(GroupName, TestName)   // Define a test function
 *          STF_TEST_TIMEOUT(Grp, Tst, Tme) // Define a test function w/ timeout
 *          STF_TEST_EXCLUDE(Group, Test)   // Specify a test to exclude
 *          STF_ASSERT_EQ(expected, actual) // Assert expected == actual
 *          STF_ASSERT_NE(a, b)             // Assert a != b
 *          STF_ASSERT_GT(a, b)             // Assert a > b
 *          STF_ASSERT_GE(a, b)             // Assert a >= b
 *          STF_ASSERT_LT(a, b)             // Assert a < b
 *          STF_ASSERT_LE(a, b)             // Assert a <= b
 *          STF_ASSERT_TRUE(a)              // Assert a is true
 *          STF_ASSERT_FALSE(a)             // Assert a is false
 *          STF_ASSERT_CLOSE(a, b, epsilon) // Assert abs(a - b) < epsilon
 *          STF_ASSERT_MEM_EQ(a, b, octets) // Assert equal memory ranges
 *          STF_ASSERT_MEM_NE(a, b, octets) // Assert non-equal memory ranges
 *          STF_ASSERT_EXCEPTION(f)         // Assert f throws any exception
 *          STF_ASSERT_EXCEPTION_E(f, e)    // Assert f throws exception e
 *
 *      When performing comparisons of user-defined types, it is important that
 *      comparison operators are defined for those types.  Further, if the
 *      comparison fails, this test framework will attempt to output the type
 *      to std::cout.  If a user-defined type does not have a streaming operator
 *      defined, the library will indicate the object is unprintable when
 *      a test fails.  One may define a streaming operator before including
 *      this header file so that the library is aware of the operator's
 *      existence.
 *
 *      To test if a function call throws an exception, one passes the name of
 *      the function to call in the macro.  The macro excepts a type of
 *      std::function<void()>.  While one can pass a std::function object, the
 *      simplest way to test exceptions is by doing the following:
 *
 *          auto test_func = [&] { SomeFunction(arg1, arg2); }
 *          STF_ASSERT_EXCEPTION(test_func)
 *
 *      Alternatively, the lambda may be inserted directly as shown:
 *
 *          STF_ASSERT_EXCEPTION([&] { SomeFunction(arg1, arg2); })
 *
 *      When testing for an explicit exception to be thrown, it is important
 *      that the exception type "e" be as specific as possible.  For example,
 *      if one passes std::exception as the exception parameter, anything
 *      thrown that is derived from std::exception (e.g., std::runtime_error)
 *      would pass the test.  Tests should specify the exact exception type
 *      expected.
 *
 *      The STF_TEST_EXCLUDE macro specifies which tests should be excludes
 *      from test runs.  This is useful if there is a known failing test that
 *      needs to be excluded temporarily or when there are some tests that need
 *      to be performed only under certain conditions that can be articulated
 *      at compile time.
 *
 *  Portability Issues:
 *      Requires C++11 or greater.
 */

#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <functional>
#include <cstdint>
#include <cstdlib>
#include <type_traits>

// Macro to define a test function and register the test for execution
#define STF_TEST(group, test) \
    void STF_Test_ ## group ## _ ## test(); \
    const std::size_t STF_Test_ID_ ## group ## _ ## test = \
        STF::RegisterTest(std::string(#group) + std::string("::") + \
                          std::string(#test), \
                          STF_Test_ ## group ## _ ## test); \
    void STF_Test_ ## group ## _ ## test()

// Macro to define a test function and register the test for execution
#define STF_TEST_TIMEOUT(group, test, timeout) \
    void STF_Test_ ## group ## _ ## test(); \
    const std::size_t STF_Test_ID_ ## group ## _ ## test = \
        STF::RegisterTest(std::string(#group) + std::string("::") + \
                          std::string(#test), \
                          STF_Test_ ## group ## _ ## test, \
                          timeout); \
    void STF_Test_ ## group ## _ ## test()

// Macro to specify a test that should be excluded from execution
#define STF_TEST_EXCLUDE(group, test) \
    const bool STF_Test_ID_ ## group ## _ ## test ## _excluded = \
        STF::ExcludeTest(std::string(#group) + std::string("::") + \
                        std::string(#test));

// Macro to test for equality
#define STF_ASSERT_EQ(expected, actual) \
    if (!((expected) == (actual))) \
    STF::ExpectFail(__FILE__, __LINE__, (expected), (actual))

// Macro to test for inequality
#define STF_ASSERT_NE(a, b) \
    if (!((a) != (b))) STF::LhsRhsFail(__FILE__, __LINE__, (a), (b))

// Macro to test that a > b
#define STF_ASSERT_GT(a, b) \
    if (!((a) > (b))) STF::LhsRhsFail(__FILE__, __LINE__, (a), (b))

// Macro to test that a >= b
#define STF_ASSERT_GE(a, b) \
    if (!((a) >= (b))) STF::LhsRhsFail(__FILE__, __LINE__, (a), (b))

// Macro to test that a < b
#define STF_ASSERT_LT(a, b) \
    if (!((a) < (b))) STF::LhsRhsFail(__FILE__, __LINE__, (a), (b))

// Macro to test that a <= b
#define STF_ASSERT_LE(a, b) \
    if (!((a) <= (b))) STF::LhsRhsFail(__FILE__, __LINE__, (a), (b))

// Macro to test for true
#define STF_ASSERT_TRUE(a) \
    STF::AssertBoolean(__FILE__, __LINE__, bool(a) == true)

// Macro to test for false
#define STF_ASSERT_FALSE(a) \
    STF::AssertBoolean(__FILE__, __LINE__, bool(a) == false)

// Macro to test that difference in float or double values are less than epsilon
#define STF_ASSERT_CLOSE(a, b, epsilon) \
    STF::AssertClose(__FILE__, __LINE__, (a), (b), (epsilon))

// Macro to test memory ranges for equality
#define STF_ASSERT_MEM_EQ(a, b, size) \
    STF::AssertMemoryEqual(__FILE__, __LINE__, (a), (b), (size))

// Macro to test memory ranges for inequality
#define STF_ASSERT_MEM_NE(a, b, size) \
    STF::AssertMemoryNotEqual(__FILE__, __LINE__, (a), (b), (size))

// Macro to test for exceptions to be thrown on a function call
#define STF_ASSERT_EXCEPTION(function) \
    STF::AssertException(__FILE__, __LINE__, (function))

// Macro to test for specific exceptions to be thrown on a function call
#define STF_ASSERT_EXCEPTION_E(function, exception) \
    STF::AssertException<exception>(__FILE__, __LINE__, (function), #exception)

//////////////////////////////////////////////////////////////////////////////
////////////////////                                   ///////////////////////
////////////////////     Internal Functions Follow     ///////////////////////
////////////////////                                   ///////////////////////
//////////////////////////////////////////////////////////////////////////////

namespace STF
{

// Default test timeout in seconds
constexpr unsigned Default_Timeout = 600;

// String Constants
extern std::string ExpectText;
extern std::string ActualText;
extern std::string LHSText;
extern std::string RHSText;

/*
 *  RegisterTest()
 *
 *  Description:
 *      Function to register a test with the Simple Test Framework.
 *
 *  Parameters:
 *      name [in]
 *          The name of the test.
 *
 *      test [in]
 *          The test routine to register.
 *
 *      timeout [in]
 *          Time after which the test will assume to have stalled and the
 *          test will be aborted.  This parameter is optional.  The default
 *          value is Default_Timeout.
 *
 *  Returns:
 *      An identifier for the registered test.
 *
 *  Comments:
 *      None.
 */
std::size_t RegisterTest(const std::string &name,
                         const std::function<void()> &test,
                         unsigned timeout = Default_Timeout);

/*
 *  ExcludeTest()
 *
 *  Description:
 *      Function to specify what tests should be excluded from test runs.
 *
 *  Parameters:
 *      name [in]
 *          The name of the test.
 *
 *  Returns:
 *      True to indicate test is recorded for exclusion.
 *
 *  Comments:
 *      None.
 */
bool ExcludeTest(const std::string &name);

/*
 *  PrintValue()
 *
 *  Description:
 *      This function will print the expect/actual string (or similar)
 *      along with the value.  This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void PrintValue(const std::string &text, bool value);

/*
 *  PrintValue()
 *
 *  Description:
 *      This function will print the expect/actual string (or similar)
 *      along with the value.  This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void PrintValue(const std::string &text, unsigned char value);

/*
 *  PrintValue()
 *
 *  Description:
 *      This function will print the expect/actual string (or similar)
 *      along with the value.  This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void PrintValue(const std::string &text, char value);

/*
 *  PrintValue()
 *
 *  Description:
 *      This function will print the expect/actual string (or similar)
 *      along with the value.  This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void PrintValue(const std::string &text, signed char value);

/*
 *  PrintValue()
 *
 *  Description:
 *      This function will print the expect/actual string (or similar)
 *      along with the value.  This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
#ifdef __cpp_char8_t
void PrintValue(const std::string &text, char8_t value);
#endif

/*
 *  PrintValue()
 *
 *  Description:
 *      This function will print the expect/actual string (or similar)
 *      along with the value.  This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
#ifdef __cpp_unicode_characters
void PrintValue(const std::string &text, char16_t value);
#endif

/*
 *  PrintValue()
 *
 *  Description:
 *      This function will print the expect/actual string (or similar)
 *      along with the value.  This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
#ifdef __cpp_unicode_characters
void PrintValue(const std::string &text, char32_t value);
#endif

/*
 *  PrintValue()
 *
 *  Description:
 *      This function will print the expect/actual string (or similar)
 *      along with the value.  This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void PrintValue(const std::string &text, wchar_t value);

/*
 *  PrintValue()
 *
 *  Description:
 *      This function prints the expect/actual string (or similar) along
 *      with the value if it has streaming operator defined. This is called
 *      by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *      _ [in]
 *          Dummy for function disambiguation.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
template<typename T>
auto PrintValue(const std::string &text, const T &value, int) ->
                                        decltype(std::cout << value, void())
{
    std::cout << text << value << std::endl;
}

/*
 *  PrintValue()
 *
 *  Description:
 *      This function prints the expect/actual string (or similar) along
 *      with a message indicating T is an unprintable object type and memory
 *      address of "value" when a streaming operator is not defined for the
 *      type T. This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *      _ [in]
 *          Dummy for function disambiguation.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
template<typename T>
auto PrintValue(const std::string &text, const T &value, long) ->
                                                            decltype(void())
{
    std::cout << text
              << "[Unprintable object at address 0x"
              << reinterpret_cast<const void *>(&value)
              << "]"
              << std::endl;
}

/*
 *  PrintValue()
 *
 *  Description:
 *      This function will print the expect/actual string (or similar)
 *      along with the value.  This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
template<typename T,
         typename std::enable_if<!std::is_integral<T>::value &&
                                 !std::is_floating_point<T>::value &&
                                 !std::is_array<T>::value &&
                                 !std::is_pointer<T>::value, bool>::type = true>
void PrintValue(const std::string &text, const T &value)
{
    PrintValue(text, value, 0);
}

/*
 *  PrintValue()
 *
 *  Description:
 *      This function will print the expect/actual string (or similar)
 *      along with the value.  This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
template<typename T,
         typename std::enable_if<std::is_array<T>::value ||
                                 std::is_pointer<T>::value, bool>::type = true>
void PrintValue(const std::string &text, const T value)
{
    std::cout << text
              << reinterpret_cast<const void *>(value)
              << " (memory address)"
              << std::endl;
}

/*
 *  PrintValue()
 *
 *  Description:
 *      This function will print the expect/actual string (or similar)
 *      along with the value.  This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
template<typename T,
         typename std::enable_if<std::is_floating_point<T>::value,
                                 bool>::type = true>
void PrintValue(const std::string &text, T value)
{
    std::ostringstream oss;

    oss << text << std::setprecision(26) << value;

    std::cout << oss.str() << std::endl;
}

/*
 *  PrintValue()
 *
 *  Description:
 *      This function will print the expect/actual string (or similar)
 *      along with the value.  This is called by failing tests.
 *
 *  Parameters:
 *      text [in]
 *          The text to print (e.g., "expected").
 *
 *      value [in]
 *          The value to print.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
template<typename T,
         typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
void PrintValue(const std::string &text, T value)
{
    std::ostringstream oss;

    oss << std::hex << std::setfill('0');

    oss << text << std::dec << value << " (0x" << std::hex
        << std::setw(sizeof(T) * 2) << +value << ")";

    std::cout << oss.str() << std::endl;
}

/*
 *  PrintAssertFailed()
 *
 *  Description:
 *      This function will print a message indicating an assertion failed.
 *
 *  Parameters:
 *      file [in]
 *          The name of the file where the test exists.
 *
 *      line [in]
 *          The line number where the test failed.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void PrintAssertFailed(const std::string &file, std::size_t line);

/*
 *  ExpectFail()
 *
 *  Description:
 *      Handle the failure case when a value does not agree with an expected
 *      value.
 *
 *  Parameters:
 *      file [in]
 *          The name of the file where the test exists.
 *
 *      line [in]
 *          The line number where the test failed.
 *
 *      expected [in]
 *          The expected value.
 *
 *      actual [in]
 *          The actual value.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
template<typename T, typename U>
void ExpectFail(const std::string &file,
                const std::size_t line,
                const T &expected,
                const U &actual)
{
    PrintAssertFailed(file, line);
    PrintValue(ExpectText, expected);
    PrintValue(ActualText, actual);

    std::exit(EXIT_FAILURE);
}

/*
 *  LhsRhsFail()
 *
 *  Description:
 *      Handle the failure cases when a lhs value does not compare as
 *      expected to a rhs value.
 *
 *  Parameters:
 *      file [in]
 *          The name of the file where the test exists.
 *
 *      line [in]
 *          The line number where the test failed.
 *
 *      lhs [in]
 *          The left-hand side value to compare.
 *
 *      rhs [in]
 *          The right-hand side value to compare.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
template<typename T, typename U>
void LhsRhsFail(const std::string &file,
                const std::size_t line,
                const T &lhs,
                const U &rhs)
{
    PrintAssertFailed(file, line);
    PrintValue(LHSText, lhs);
    PrintValue(RHSText, rhs);

    std::exit(EXIT_FAILURE);
}

/*
 *  AssertBoolean()
 *
 *  Description:
 *      Test that the given value is true.
 *
 *  Parameters:
 *      file [in]
 *          The name of the file where the test exists.
 *
 *      line [in]
 *          The line number where the test failed.
 *
 *      value [in]
 *          The value to check to be true.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void AssertBoolean(const std::string &file, std::size_t line, bool value);

/*
 *  AssertClose()
 *
 *  Description:
 *      Test that the absolute value of the difference between the left-hand
 *      side value and the right-hand side value is less than epsilon.
 *
 *  Parameters:
 *      file [in]
 *          The name of the file where the test exists.
 *
 *      line [in]
 *          The line number where the test failed.
 *
 *      lhs [in]
 *          The left-hand side value to compare.
 *
 *      rhs [in]
 *          The right-hand side value to compare.
 *
 *      epsilon [in]
 *          The value of which the absolute value of the difference between
 *          the left-hand side and right-hand side value can be no greater.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void AssertClose(const std::string &file,
                 const std::size_t line,
                 float lhs,
                 float rhs,
                 float epsilon);

/*
 *  AssertClose()
 *
 *  Description:
 *      Test that the absolute value of the difference between the left-hand
 *      side value and the right-hand side value is less than epsilon.
 *
 *  Parameters:
 *      file [in]
 *          The name of the file where the test exists.
 *
 *      line [in]
 *          The line number where the test failed.
 *
 *      lhs [in]
 *          The left-hand side value to compare.
 *
 *      rhs [in]
 *          The right-hand side value to compare.
 *
 *      epsilon [in]
 *          The value of which the absolute value of the difference between
 *          the left-hand side and right-hand side value can be no greater.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void AssertClose(const std::string &file,
                 const std::size_t line,
                 double lhs,
                 double rhs,
                 double epsilon);

/*
 *  AssertClose()
 *
 *  Description:
 *      Test that the absolute value of the difference between the left-hand
 *      side value and the right-hand side value is less than epsilon.
 *
 *  Parameters:
 *      file [in]
 *          The name of the file where the test exists.
 *
 *      line [in]
 *          The line number where the test failed.
 *
 *      lhs [in]
 *          The left-hand side value to compare.
 *
 *      rhs [in]
 *          The right-hand side value to compare.
 *
 *      epsilon [in]
 *          The value of which the absolute value of the difference between
 *          the left-hand side and right-hand side value can be no greater.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void AssertClose(const std::string &file,
                 const std::size_t line,
                 long double lhs,
                 long double rhs,
                 long double epsilon);

/*
 *  AssertMemoryEqual()
 *
 *  Description:
 *      Test that two blocks of memory of length "length" pointed to by
 *      "expected" and "actual" contain the same values.
 *
 *  Parameters:
 *      file [in]
 *          The name of the file where the test exists.
 *
 *      line [in]
 *          The line number where the test failed.
 *
 *      expected [in]
 *          A pointer to the memory containing the expected values.
 *
 *      actual [in]
 *          A pointer to the memory containing the actual values.
 *
 *      length [in]
 *          The number of octets of memory to compare.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void AssertMemoryEqual(const std::string &file,
                       const std::size_t line,
                       const void *expected,
                       const void *actual,
                       std::size_t length);

/*
 *  AssertMemoryNotEqual()
 *
 *  Description:
 *      Test that two blocks of memory of length "length" pointed to by
 *      "lhs" and "rhs" contain different values.
 *
 *  Parameters:
 *      file [in]
 *          The name of the file where the test exists.
 *
 *      line [in]
 *          The line number where the test failed.
 *
 *      lhs [in]
 *          A pointer to the memory to compare.
 *
 *      rhs [in]
 *          A pointer to the memory to compare.
 *
 *      length [in]
 *          The number of octets of memory to compare.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void AssertMemoryNotEqual(const std::string &file,
                          const std::size_t line,
                          const void *lhs,
                          const void *rhs,
                          std::size_t length);

/*
 *  AssertException()
 *
 *  Description:
 *      Test that a function throws an exception.  This test will succeed
 *      if an exception is thrown.  Exceptions thrown will be caught and
 *      execution will continue as expected.
 *
 *  Parameters:
 *      file [in]
 *          The name of the file where the test exists.
 *
 *      line [in]
 *          The line number where the test failed.
 *
 *      function [in]
 *          A function to invoke to check for exceptions.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      None.
 */
void AssertException(const std::string &file,
                     const std::size_t line,
                     const std::function<void()> function);

/*
 *  AssertException()
 *
 *  Description:
 *      Test that a function throws a specific type of exception.  This test
 *      will succeed only if an exception of the specified type T is thrown.
 *
 *  Parameters:
 *      file [in]
 *          The name of the file where the test exists.
 *
 *      line [in]
 *          The line number where the test failed.
 *
 *      function [in]
 *          A function to invoke to check for exceptions.
 *
 *      exception_name [in]
 *          The name of the expected exception.
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      Note that if testing generically for something like std::exception,
 *      any exception derived from std::exception will pass.  Tests should
 *      be as specific as necessary to ensure expected results.
 */
template<typename T>
void AssertException(const std::string &file,
                     const std::size_t line,
                     const std::function<void()> function,
                     const std::string exception_name)
{
    bool exception_thrown = false;
    bool expected_exception = false;

    try
    {
        function();
    }
    catch (const T &)
    {
        exception_thrown = true;
        expected_exception = true;
    }
    catch (...)
    {
        exception_thrown = true;
    }

    if (!expected_exception)
    {
        PrintAssertFailed(file, line);
        PrintValue(ExpectText,
                    std::string("exception of type ") + exception_name);
        if (exception_thrown)
        {
            PrintValue(ActualText, std::string("some other exception thrown"));
        }
        else
        {
            PrintValue(ActualText, std::string("no exception thrown"));
        }
        std::exit(EXIT_FAILURE);
    }
}

} // Namespace STF
