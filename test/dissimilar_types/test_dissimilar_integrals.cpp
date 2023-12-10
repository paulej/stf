/*
 *  test_dissimilar_integrals.cpp
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      Module to exercise tests that use dissimilar integrals, such as int
 *      compared to long int.
 *
 *  Portability Issues:
 *      None.
 */

#include <cstdint>
#include <stf/stf.h>

STF_TEST(DissimilarTypes, Equal)
{
    {
        char i = 'a';
        unsigned char j = 'a';

        STF_ASSERT_EQ(i, j);
    }

    {
        int i = 1;
        long j = 1;

        STF_ASSERT_EQ(i, j);
    }

    {
        std::uint32_t i = 1;
        std::uint64_t j = 1;

        STF_ASSERT_EQ(i, j);
    }

    {
        std::uint64_t i = 0;

        STF_ASSERT_EQ(0U, i);
    }
}

STF_TEST(DissimilarTypes, Inequality)
{
    {
        char i = 'a';
        unsigned char j = 'b';

        STF_ASSERT_NE(i, j);
    }

    {
        int i = 1;
        long j = 2;

        STF_ASSERT_NE(i, j);
    }

    {
        std::uint32_t i = 1;
        std::uint64_t j = 2;

        STF_ASSERT_NE(i, j);
    }
}

STF_TEST(DissimilarTypes, Greater)
{
    {
        char i = 'b';
        unsigned char j = 'a';

        STF_ASSERT_GT(i, j);
    }

    {
        int i = 2;
        long j = 1;

        STF_ASSERT_GT(i, j);
    }

    {
        std::uint32_t i = 2;
        std::uint64_t j = 1;

        STF_ASSERT_GT(i, j);
    }
}

STF_TEST(DissimilarTypes, GreaterEqual)
{
    {
        char i = 'a';
        unsigned char j = 'a';

        STF_ASSERT_GE(i, j);
    }

    {
        int i = 2;
        long j = 1;

        STF_ASSERT_GE(i, j);
    }

    {
        std::uint32_t i = 2;
        std::uint64_t j = 1;

        STF_ASSERT_GE(i, j);
    }

    {
        int i = 2;
        int j = 2;

        STF_ASSERT_GE(i, j);
    }

    {
        std::uint32_t i = 2;
        std::uint64_t j = 2;

        STF_ASSERT_GE(i, j);
    }
}

STF_TEST(DissimilarTypes, Less)
{
    {
        char i = 'a';
        unsigned char j = 'b';

        STF_ASSERT_LT(i, j);
    }

    {
        int i = 1;
        long j = 2;

        STF_ASSERT_LT(i, j);
    }

    {
        std::uint32_t i = 1;
        std::uint64_t j = 2;

        STF_ASSERT_LT(i, j);
    }
}

STF_TEST(DissimilarTypes, LessEqual)
{
    {
        char i = 'a';
        unsigned char j = 'a';

        STF_ASSERT_LE(i, j);
    }

    {
        int i = 1;
        long j = 2;

        STF_ASSERT_LE(i, j);
    }

    {
        std::uint32_t i = 1;
        std::uint64_t j = 2;

        STF_ASSERT_LE(i, j);
    }

    {
        int i = 2;
        int j = 2;

        STF_ASSERT_LE(i, j);
    }

    {
        std::uint32_t i = 2;
        std::uint64_t j = 2;

        STF_ASSERT_LE(i, j);
    }
}

STF_TEST(DissimilarTypes, True)
{
    {
        char i = 'a';
        unsigned char j = 'b';

        STF_ASSERT_TRUE(i != j);
    }

    {
        int i = 1;
        long j = 2;

        STF_ASSERT_TRUE(i != j);
    }

    {
        std::uint32_t i = 1;
        std::uint64_t j = 2;

        STF_ASSERT_TRUE(i != j);
    }
}

STF_TEST(DissimilarTypes, False)
{
    {
        char i = 'a';
        unsigned char j = 'b';

        STF_ASSERT_FALSE(i == j);
    }

    {
        int i = 1;
        long j = 2;

        STF_ASSERT_FALSE(i == j);
    }

    {
        std::uint32_t i = 1;
        std::uint64_t j = 2;

        STF_ASSERT_FALSE(i == j);
    }
}
