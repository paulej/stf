/*
 *  stf.cpp
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      This is the implementation module for the Simple Test Framework.
 *      It defines a few functions in the STF namespace that are used to
 *      register tests, produce output, and perform some comparison operations.
 *
 *      This file also includes the main() function that iterates over the
 *      vector of registered unit tests, invokes each test function, and prints
 *      timing information.
 *
 *  Portability Issues:
 *      Requires C++11 or greater.
 */

#include <tuple>
#include <vector>
#include <cctype>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <mutex>
#include <cstdlib>
#include <typeinfo>
#include <stf/stf.h>
#include "version.h"

namespace STF
{

// String constants used when producing failure messages
std::string ExpectText = "  expected: ";
std::string ActualText = "    actual: ";
std::string LHSText = "  lhs: ";
std::string RHSText = "  rhs: ";

// Define a vector to hold unit test functions to execute
using UnitTests = std::vector<std::tuple<std::string,
                              std::function<void()>,
                              unsigned>>;

// Define a vector to hold unit test names to exclude from running
using UnitTestExclusions = std::vector<std::string>;

// Define a shared pointer for the aforementioned UnitTests
static std::shared_ptr<UnitTests> Unit_Tests;

// Define a shared pointer for tests that should be excluded
static std::shared_ptr<UnitTestExclusions> Unit_Test_Exclusions;

/*
 *  RegisterTest()
 *
 *  Description:
 *      Function to register a unit test with the Simple Test Framework.
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
                         unsigned timeout)
{
    // If this is the first test, allocate storage
    if (!Unit_Tests) Unit_Tests = std::make_shared<UnitTests>();

    // Store this test in the unit test vector
    Unit_Tests->push_back({name, test, timeout});

    return Unit_Tests->size();
}

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
bool ExcludeTest(const std::string &name)
{
    // If this is the first test exclusion, allocate storage
    if (!Unit_Test_Exclusions)
    {
        Unit_Test_Exclusions = std::make_shared<UnitTestExclusions>();
    }

    // Store this test in the unit test vector
    Unit_Test_Exclusions->push_back(name);

    return true;
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
void PrintValue(const std::string &text, bool value)
{
    std::ostringstream oss;

    oss << text << std::boolalpha << value;

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
void PrintValue(const std::string &text, unsigned char value)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    oss << text;
    if (std::isprint(value)) oss << "'" << value << "' ";
    oss << "(unsigned char 0x" << std::setw(2) << +value << ")";

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
void PrintValue(const std::string &text, char value)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    oss << text;
    if (std::isprint(value)) oss << "'" << value << "' ";
    oss << "(char 0x"
        << std::setw(2)
        << +static_cast<unsigned char>(value)
        << ")";

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
void PrintValue(const std::string &text, signed char value)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    oss << text;
    if (std::isprint(value)) oss << "'" << value << "' ";
    oss << "(signed char 0x"
        << std::setw(2)
        << +static_cast<unsigned char>(value)
        << ")";

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
#ifdef __cpp_char8_t
void PrintValue(const std::string &text, char8_t value)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    oss << text;
    if (std::isprint(value)) oss << "'" << static_cast<char>(value) << "' ";
    oss << "(char8_t 0x" << std::setw(2) << +value << ")";

    std::cout << oss.str() << std::endl;
}
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
void PrintValue(const std::string &text, char16_t value)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    oss << text << "char16_t 0x" << std::setw(4)
        << +static_cast<std::uint16_t>(value);

    std::cout << oss.str() << std::endl;
}
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
void PrintValue(const std::string &text, char32_t value)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    oss << text << "char32_t 0x" << std::setw(8)
        << +static_cast<std::uint32_t>(value);

    std::cout << oss.str() << std::endl;
}
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
void PrintValue(const std::string &text, wchar_t value)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    static_assert(sizeof(wchar_t) <= 4, "Unsupported wchar_t size");

    // This type varies in size by platform, either 16 or 32 bits observed
    if (sizeof(wchar_t) == 2)
    {
        oss << text << "wchar_t 0x" << std::setw(4)
            << +static_cast<std::uint16_t>(value);
    }
    else if (sizeof(wchar_t) == 4)
    {
        oss << text << "wchar_t 0x" << std::setw(8)
            << +static_cast<std::uint32_t>(value);
    }

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
void PrintAssertFailed(const std::string &file, std::size_t line)
{
    std::cout << std::endl;
    std::cout << "Assertion failed at " << file << ":" << line << std::endl;
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
void AssertBoolean(const std::string &file, std::size_t line, bool value)
{
    if (value) return;

    PrintAssertFailed(file, line);

    std::exit(EXIT_FAILURE);
}

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
                 float epsilon)
{
    if (fabsf(lhs - rhs) < epsilon) return;

    PrintAssertFailed(file, line);
    PrintValue(LHSText, lhs);
    PrintValue(RHSText, rhs);

    std::exit(EXIT_FAILURE);
}

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
                 double epsilon)
{
    if (fabs(lhs - rhs) < epsilon) return;

    PrintAssertFailed(file, line);
    PrintValue(LHSText, lhs);
    PrintValue(RHSText, rhs);

    std::exit(EXIT_FAILURE);
}

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
                 long double epsilon)
{
    if (fabsl(lhs - rhs) < epsilon) return;

    PrintAssertFailed(file, line);
    PrintValue(LHSText, lhs);
    PrintValue(RHSText, rhs);

    std::exit(EXIT_FAILURE);
}

/*
 *  GetMemoryHex()
 *
 *  Description:
 *      Creates a string containing hex values from a block of memory.
 *
 *  Parameters:
 *      memory [in]
 *          A pointer into memory.
 *
 *      length [in]
 *          The number of octets to read from memory and convert into a hex
 *          string.
 *
 *  Returns:
 *      The hex string produced by this routine.
 *
 *  Comments:
 *      None.
 */
static std::string GetMemoryHex(const std::uint8_t *memory, std::size_t length)
{
    std::ostringstream oss;

    oss << std::hex << std::setfill('0');

    for (std::size_t i = 0; i < length; i++)
    {
        if (i) oss << " ";
        oss << std::setw(2) << +memory[i];
    }

    return oss.str();
}

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
                       std::size_t length)
{
    bool equal = true;

    // Convert pointers to uint8_t *
    const std::uint8_t *left = static_cast<const std::uint8_t *>(expected);
    const std::uint8_t *right = static_cast<const std::uint8_t *>(actual);

    // Check for any differences
    for (std::size_t i = 0; i < length; i++)
    {
        if (left[i] != right[i])
        {
            equal = false;
            break;
        }
    }

    if (!equal)
    {
        PrintAssertFailed(file, line);
        std::cout << ExpectText << "0x" << GetMemoryHex(left, length)
                  << std::endl
                  << ActualText << "0x" << GetMemoryHex(right, length)
                  << std::endl;

        std::exit(EXIT_FAILURE);
    }
}

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
                          std::size_t length)
{
    bool equal = true;

    // Convert pointers to uint8_t *
    const std::uint8_t *left = static_cast<const std::uint8_t *>(lhs);
    const std::uint8_t *right = static_cast<const std::uint8_t *>(rhs);

    // Check for any differences
    for (std::size_t i = 0; i < length; i++)
    {
        if (left[i] != right[i])
        {
            equal = false;
            break;
        }
    }

    if (equal)
    {
        PrintAssertFailed(file, line);
        std::cout << LHSText << "0x" << GetMemoryHex(left, length)
                  << std::endl
                  << RHSText << "0x" << GetMemoryHex(right, length)
                  << std::endl;

        std::exit(EXIT_FAILURE);
    }
}

/*
 *  AssertException()
 *
 *  Description:
 *      Test that a function throws an exception.  This test will succeed
 *      if an exception is thrown.  That exception will be caught, if so,
 *      and execution will continue as expected.
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
                     const std::function<void()> function)
{
    bool exception_thrown = false;

    try
    {
        function();
    }
    catch (...)
    {
        exception_thrown = true;
    }

    if (!exception_thrown)
    {
        PrintAssertFailed(file, line);
        PrintValue(ExpectText, std::string("any exception thrown"));
        PrintValue(ActualText, std::string("no exception thrown"));
        std::exit(EXIT_FAILURE);
    }
}

/*
 *  FriendlyDuration()
 *
 *  Description:
 *      Return a human-friendly duration string that uses seconds, milliseconds,
 *      microseconds, or nanoseconds depending on the value of the duration.
 *
 *  Parameters:
 *      duration [in]
 *          The duration to print.
 *
 *  Returns:
 *      Human-friendly duration string.
 *
 *  Comments:
 *      None.
 */
static std::string FriendlyDuration(std::chrono::nanoseconds &duration)
{
    std::ostringstream oss;

    // Should we produce seconds?
    if (duration >= std::chrono::seconds(1))
    {
        // Convert to microseconds to get fractional output
        oss << static_cast<double>(
                   std::chrono::duration_cast<std::chrono::milliseconds>(
                       duration).count()) / 1000.0
            << " s";
        return oss.str();
    }

    // Should we produce milliseconds?
    if (duration >= std::chrono::milliseconds(1))
    {
        // Convert to microseconds to get fractional output
        oss << static_cast<double>(
                   std::chrono::duration_cast<std::chrono::microseconds>(
                       duration).count()) / 1000.0
            << " ms";
        return oss.str();
    }

    // Produce fractional microsecond output
    oss << static_cast<double>(
               std::chrono::duration_cast<std::chrono::nanoseconds>(duration)
                   .count()) / 1000.0
        << " us";

    return oss.str();
}

} // Namespace STF

/*
 *  main()
 *
 *  Description:
 *      Main entry point for test execution.
 *
 *  Parameters:
 *      None.
 *
 *  Returns:
 *      0 if all tests ran successfully, non-zero otherwise.
 *
 *  Comments:
 *      None.
 */
int main()
{
    // Total test duration
    std::chrono::nanoseconds total_duration{};

    // Check that there are registered unit test
    if (!STF::Unit_Tests || STF::Unit_Tests->empty())
    {
        std::cout << "Error: there are no registered tests" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::cout << "Total numbers of tests: "
              << STF::Unit_Tests->size()
              << std::endl;

    try
    {
        // Iterate over all of the tests found, executing each in turn
        for (const auto &unit_test : *STF::Unit_Tests)
        {
            std::condition_variable cv;
            std::mutex test_mutex;
            std::string name;
            std::function<void()> test;
            unsigned timeout;
            std::chrono::steady_clock::time_point test_start_time;
            std::chrono::steady_clock::time_point test_end_time;

            // Get the test name, function, and timeout period
            std::tie(name, test, timeout) = unit_test;

            // Check to see if the test is to be excluded
            if (STF::Unit_Test_Exclusions)
            {
                bool exclude_test = false;

                // Iterate over the vector to see if the test is excluded
                for (const auto &exclusion : *STF::Unit_Test_Exclusions)
                {
                    // If the test name is found, indicate it is excluded
                    if (exclusion == name)
                    {
                        exclude_test = true;
                        break;
                    }
                }

                // If excluding the test, indicate such and continue
                if (exclude_test)
                {
                    std::cout << "Excluding test " << name << std::endl;
                    continue;
                }
            }

            std::cout << "Running test " << name << std::flush;

            // Lock the mutex to ensure proper thread synchronization
            std::unique_lock<std::mutex> lock(test_mutex);

            // Invoke the test on a separate thread
            std::thread test_thread = std::thread(
                [&]()
                {
                    // Get the start time
                    test_start_time = std::chrono::steady_clock::now();

                    // Invoke the test
                    try
                    {
                        test();
                    }
                    catch (const std::exception &e)
                    {
                        std::cout << std::endl;
                        std::cout << "Unexpected exception thrown: " << e.what()
                                  << std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    catch (...)
                    {
                        std::cout << std::endl;
                        std::cout << "Unexpected exception thrown" << std::endl;
                        std::exit(EXIT_FAILURE);
                    }

                    // Get the end time
                    test_end_time = std::chrono::steady_clock::now();

                    // Alert the main thread that the test has completed
                    std::lock_guard<std::mutex> lock(test_mutex);
                    cv.notify_one();
                });

            // Wait for the test to complete, exiting if it timed out
            if (cv.wait_for(lock, std::chrono::seconds(timeout)) ==
                                                        std::cv_status::timeout)
            {
                std::cout << std::endl
                          << "Test \""
                          << name
                          << "\" exceeded "
                          << timeout
                          << " second timeout; terminating"
                          << std::endl;
                std::exit(EXIT_FAILURE);
            }

            // Join the test thread
            test_thread.join();

            // Compute the duration for this test
            std::chrono::nanoseconds test_duration =
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    test_end_time - test_start_time);

            // Print the time
            std::cout << " ("
                      << STF::FriendlyDuration(test_duration)
                      << ")"
                      << std::endl;

            // Update the total for all tests
            total_duration += test_duration;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << std::endl;
        std::cout << "Unexpected exception thrown: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    catch (...)
    {
        std::cout << std::endl;
        std::cout << "Unexpected exception thrown" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::cout << "All test(s) passed successfully ("
              << STF::FriendlyDuration(total_duration)
              << " total)"
              << std::endl;
}
