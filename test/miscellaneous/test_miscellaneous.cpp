/*
 *  test_miscellaneous.cpp
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      Module to exercise miscellaneous STF functions.
 *
 *  Portability Issues:
 *      None.
 */

#include <stf/stf.h>

STF_TEST(Miscellaneous, TestToRun)
{
    STF_ASSERT_TRUE(true);
}

STF_TEST(Miscellaneous, TestToExclude)
{
    // This test should be excluded from running via the STF_TEST_EXCLUDE
    // macro elsewhere in this file, thus avoiding this deliberate test failure
    STF_ASSERT_TRUE(false);
}

STF_TEST(Miscellaneous, AnotherTestToRun)
{
    STF_ASSERT_TRUE(true);
}

STF_TEST(Miscellaneous, SecondTestToExclude)
{
    // This test should be excluded from running via the STF_TEST_EXCLUDE
    // macro elsewhere in this file, thus avoiding this deliberate test failure
    STF_ASSERT_TRUE(false);
}

// Indicate tests to exclude
STF_TEST_EXCLUDE(Miscellaneous, TestToExclude)
STF_TEST_EXCLUDE(Miscellaneous, SecondTestToExclude)
