/*
 *  test_objects.cpp
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      Module to exercise tests related to objects.
 *
 *  Portability Issues:
 *      None.
 */

#include "some_object.h"
#include <stf/stf.h>

STF_TEST(Objects, Equal)
{
    SomeObject object1(10);
    SomeObject object2(10);

    STF_ASSERT_EQ(object1, object2);
}

STF_TEST(Objects, Inequality)
{
    SomeObject object1(10);
    SomeObject object2(20);

    STF_ASSERT_NE(object1, object2);
}

STF_TEST(Objects, Greater)
{
    SomeObject object1(20);
    SomeObject object2(10);

    STF_ASSERT_GT(object1, object2);
}

STF_TEST(Objects, GreaterEqual)
{
    SomeObject object1(10);
    SomeObject object2(10);

    STF_ASSERT_GE(object1, object2);
}

STF_TEST(Objects, Less)
{
    SomeObject object1(10);
    SomeObject object2(20);

    STF_ASSERT_LT(object1, object2);
}

STF_TEST(Objects, LessEqual)
{
    SomeObject object1(20);
    SomeObject object2(20);

    STF_ASSERT_LE(object1, object2);
}

STF_TEST(Objects, True)
{
    SomeObject object1(20);
    SomeObject object2(20);

    STF_ASSERT_TRUE(object1 == object2);
}

STF_TEST(Objects, False)
{
    SomeObject object1(10);
    SomeObject object2(20);

    STF_ASSERT_FALSE(object1 == object2);
}
