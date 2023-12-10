/*
 *  test_floats.cpp
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      Module to exercise tests related to floating point numbers using
 *      the Simple Test Framework library.
 *
 *  Portability Issues:
 *      None.
 */

#include <stf/stf.h>

STF_TEST(Floats, SingleEquality)
{
    float i = 0.0f;
    float j = 0.0f;

    STF_ASSERT_EQ(i, j);
}

STF_TEST(Floats, DoubleEquality)
{
    double i = 0.0;
    double j = 0.0;

    STF_ASSERT_EQ(i, j);
}

STF_TEST(Floats, SingleInequality)
{
    float i = 0.0f;
    float j = 1.0f;

    STF_ASSERT_NE(i, j);
}

STF_TEST(Floats, DoubleInequality)
{
    double i = 0.0;
    double j = 1.0;

    STF_ASSERT_NE(i, j);
}

STF_TEST(Floats, SingleGreater)
{
    float i = 3.14f;
    float j = 1.0f;

    STF_ASSERT_GT(i, j);
}

STF_TEST(Floats, DoubleGreater)
{
    double i = 3.14;
    double j = 1.0;

    STF_ASSERT_GT(i, j);
}

STF_TEST(Floats, SingleGreaterEqual)
{
    float i = 3.14f;
    float j = 1.0f;

    STF_ASSERT_GE(i, j);

    float k = 3.14f;
    float l = 3.14f;

    STF_ASSERT_GE(k, l);
}

STF_TEST(Floats, DoubleGreaterEqual)
{
    double i = 3.14;
    double j = 1.0;

    STF_ASSERT_GE(i, j);

    double k = 3.14;
    double l = 3.14;

    STF_ASSERT_GE(k, l);
}

STF_TEST(Floats, SingleLess)
{
    float i = 1.0f;
    float j = 3.14f;

    STF_ASSERT_LT(i, j);
}

STF_TEST(Floats, DoubleLess)
{
    float i = 1.0f;
    float j = 3.14f;

    STF_ASSERT_LT(i, j);
}

STF_TEST(Floats, SingleLessEqual)
{
    float i = 1.0f;
    float j = 3.14f;

    STF_ASSERT_LE(i, j);

    float k = 3.14f;
    float l = 3.14f;

    STF_ASSERT_LE(k, l);
}

STF_TEST(Floats, DoubleLessEqual)
{
    float i = 1.0f;
    float j = 3.14f;

    STF_ASSERT_LE(i, j);

    float k = 3.14f;
    float l = 3.14f;

    STF_ASSERT_LE(k, l);
}

STF_TEST(Floats, SingleClose)
{
    float f1 = 100.00001f;
    float f2 = 100.00002f;

    STF_ASSERT_CLOSE(f1, f2, 0.0001f);
}

STF_TEST(floats, DoubleClose)
{
    double d1 = 100.0000001;
    double d2 = 100.0000002;

    STF_ASSERT_CLOSE(d1, d2, 0.00001);
}

STF_TEST(floats, SingleTrue)
{
    float i = 3.14f;
    float j = 3.14f;

    STF_ASSERT_TRUE(i == j);
}

STF_TEST(floats, DoubleTrue)
{
    double i = 3.14;
    double j = 3.14;

    STF_ASSERT_TRUE(i == j);
}

STF_TEST(floats, SingleFalse)
{
    float i = 3.14f;
    float j = 2.75f;

    STF_ASSERT_FALSE(i == j);
}

STF_TEST(floats, DoubleFalse)
{
    double i = 3.14;
    double j = 2.75;

    STF_ASSERT_FALSE(i == j);
}
