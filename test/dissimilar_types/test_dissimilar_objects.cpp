/*
 *  test_dissimilar_objects.cpp
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      Module to exercise tests related to dissimilar, but related, objects.
 *
 *  Portability Issues:
 *      None.
 */

#include "dissimilar_objects.h"
#include <stf/stf.h>

STF_TEST(DissimilarObjects, Equal)
{
    SomeObject object1(10);
    SomeOtherObject object2(10);

    STF_ASSERT_EQ(object1, object2);
}

STF_TEST(DissimilarObjects, Inequality)
{
    SomeObject object1(10);
    SomeOtherObject object2(20);

    STF_ASSERT_NE(object1, object2);
    STF_ASSERT_NE(object2, object1);
}

STF_TEST(DissimilarObjects, Greater)
{
    SomeObject object1(20);
    SomeOtherObject object2(10);

    STF_ASSERT_GT(object1, object2);
}

STF_TEST(DissimilarObjects, GreaterEqual)
{
    SomeObject object1(10);
    SomeOtherObject object2(10);

    STF_ASSERT_GE(object1, object2);
}

STF_TEST(DissimilarObjects, Less)
{
    SomeObject object1(10);
    SomeOtherObject object2(20);

    STF_ASSERT_LT(object1, object2);
}

STF_TEST(DissimilarObjects, LessEqual)
{
    SomeObject object1(20);
    SomeOtherObject object2(20);

    STF_ASSERT_LE(object1, object2);
}

STF_TEST(DissimilarObjects, True)
{
    SomeObject object1(20);
    SomeOtherObject object2(20);

    STF_ASSERT_TRUE(object1 == object2);
}

STF_TEST(DissimilarObjects, False)
{
    SomeObject object1(10);
    SomeOtherObject object2(20);

    STF_ASSERT_FALSE(object1 == object2);
}
