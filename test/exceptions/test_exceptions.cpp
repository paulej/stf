/*
 *  test_exceptions.cpp
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      Module to exercise tests related to function calls that should throw
 *      exceptions.
 *
 *  Portability Issues:
 *      None.
 */

#include <stdexcept>
#include <stf/stf.h>

class CustomException : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

STF_TEST(Exceptions, TestThrowUnnamed)
{
    auto test_throw_unnamed = [] { throw "Unnamed"; };

    STF_ASSERT_EXCEPTION(test_throw_unnamed);
}

STF_TEST(Exceptions, TestExpectedException)
{
    auto test_throw_named = [] { throw CustomException(""); };

    STF_ASSERT_EXCEPTION_E(test_throw_named, CustomException);
}

// Note this will pass since CustomException derives from std::runtime_error
STF_TEST(Exceptions, TestExpectedException2)
{
    auto test_throw_named = [] { throw CustomException(""); };

    STF_ASSERT_EXCEPTION_E(test_throw_named, std::runtime_error);
}

STF_TEST(Exceptions, TestDirectLambdaInsertion1)
{
    STF_ASSERT_EXCEPTION([] { throw CustomException(""); });
}

STF_TEST(Exceptions, TestDirectLambdaInsertion2)
{
    STF_ASSERT_EXCEPTION_E([] { throw CustomException(""); }, CustomException);
}
