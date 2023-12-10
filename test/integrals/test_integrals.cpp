/*
 *  test_integrals.cpp
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      Module to exercise tests related to integrals using the Simple Test
 *      Framework library.
 *
 *  Portability Issues:
 *      None.
 */

#include <cstdint>
#include <stf/stf.h>

STF_TEST(Integrals, Equal)
{
    {
        bool a = true;
        bool b = true;

        STF_ASSERT_EQ(a, b);
    }

    {
        char i = 'a';
        char j = 'a';

        STF_ASSERT_EQ(i, j);
    }

    {
        int i = 1;
        int j = 1;

        STF_ASSERT_EQ(i, j);
    }

    {
        std::uint64_t i = 1;
        std::uint64_t j = 1;

        STF_ASSERT_EQ(i, j);
    }

    {
        std::int64_t i = 1;

        STF_ASSERT_EQ(1, i);
    }

    {
        std::uint64_t i = 1;

        STF_ASSERT_EQ(1, i);
    }
}

STF_TEST(Integrals, Inequality)
{
    {
        bool a = true;
        bool b = false;

        STF_ASSERT_NE(a, b);
    }

    {
        char i = 'a';
        char j = 'b';

        STF_ASSERT_NE(i, j);
    }

    {
        signed char i = (signed char)char(140);
        unsigned char j = char(140);

        STF_ASSERT_NE(i, j);
    }

    {
        int i = 1;
        int j = 2;

        STF_ASSERT_NE(i, j);
    }

    {
        std::uint64_t i = 1;
        std::uint64_t j = 2;

        STF_ASSERT_NE(i, j);
    }

    {
        std::int64_t i = 1;

        STF_ASSERT_NE(0, i);
    }

    {
        std::uint64_t i = 1;

        STF_ASSERT_NE(0, i);
    }
}

STF_TEST(Integrals, Greater)
{
    {
        char i = 'b';
        char j = 'a';

        STF_ASSERT_GT(i, j);
    }

    {
        int i = 2;
        int j = 1;

        STF_ASSERT_GT(i, j);
    }

    {
        std::uint64_t i = 2;
        std::uint64_t j = 1;

        STF_ASSERT_GT(i, j);
    }
}

STF_TEST(Integrals, GreaterEqual)
{
    {
        char i = 'a';
        char j = 'a';

        STF_ASSERT_GE(i, j);
    }

    {
        int i = 2;
        int j = 1;

        STF_ASSERT_GE(i, j);
    }

    {
        std::uint64_t i = 2;
        std::uint64_t j = 1;

        STF_ASSERT_GE(i, j);
    }

    {
        int i = 2;
        int j = 2;

        STF_ASSERT_GE(i, j);
    }

    {
        std::uint64_t i = 2;
        std::uint64_t j = 2;

        STF_ASSERT_GE(i, j);
    }
}

STF_TEST(Integrals, Less)
{
    {
        char i = 'a';
        char j = 'b';

        STF_ASSERT_LT(i, j);
    }

    {
        int i = 1;
        int j = 2;

        STF_ASSERT_LT(i, j);
    }

    {
        std::uint64_t i = 1;
        std::uint64_t j = 2;

        STF_ASSERT_LT(i, j);
    }
}

STF_TEST(Integrals, LessEqual)
{
    {
        char i = 'a';
        char j = 'a';

        STF_ASSERT_LE(i, j);
    }

    {
        int i = 1;
        int j = 2;

        STF_ASSERT_LE(i, j);
    }

    {
        std::uint64_t i = 1;
        std::uint64_t j = 2;

        STF_ASSERT_LE(i, j);
    }

    {
        int i = 2;
        int j = 2;

        STF_ASSERT_LE(i, j);
    }

    {
        std::uint64_t i = 2;
        std::uint64_t j = 2;

        STF_ASSERT_LE(i, j);
    }
}

STF_TEST(Integrals, True)
{
    {
        bool a = true;
        bool b = false;

        STF_ASSERT_TRUE(a != b);
    }

    {
        char i = 'a';
        char j = 'b';

        STF_ASSERT_TRUE(i != j);
    }

    {
        int i = 1;
        int j = 2;

        STF_ASSERT_TRUE(i != j);
    }

    {
        std::uint64_t i = 1;
        std::uint64_t j = 2;

        STF_ASSERT_TRUE(i != j);
    }
}

STF_TEST(Integrals, False)
{
    {
        bool a = true;
        bool b = false;

        STF_ASSERT_FALSE(a == b);
    }

    {
        char i = 'a';
        char j = 'b';

        STF_ASSERT_FALSE(i == j);
    }

    {
        int i = 1;
        int j = 2;

        STF_ASSERT_FALSE(i == j);
    }

    {
        std::uint64_t i = 1;
        std::uint64_t j = 2;

        STF_ASSERT_FALSE(i == j);
    }
}

STF_TEST(Integrals, Close)
{
    {
        float f = 3.011f;
        float g = 3.013f;

        STF_ASSERT_CLOSE(f, g, 0.005f);
    }

    {
        double f = 3.011;
        double g = 3.013;

        STF_ASSERT_CLOSE(f, g, 0.005);
    }

    {
        long double f = 3.011;
        long double g = 3.013;

        STF_ASSERT_CLOSE(f, g, 0.005L);
    }
}

STF_TEST(Integrals, VariousCharTypes)
{
#ifdef __cpp_char8_t
    {
        char8_t i = 0x41;
        char8_t j = 0x41;

        STF_ASSERT_EQ(i, j);
    }
#endif

#ifdef __cpp_unicode_characters
    {
        char16_t i = 0x5c0f;
        char16_t j = 0x5c0f;

        STF_ASSERT_EQ(i, j);
    }

    {
        char32_t i = 0x00005c0f;
        char32_t j = 0x00005c0f;

        STF_ASSERT_EQ(i, j);
    }

    {
        char32_t i = 0x00005c0f;
        char32_t j = 0x00005c0f;

        STF_ASSERT_EQ(i, j);
    }
#endif

    if (sizeof(wchar_t) == 2)
    {
        wchar_t i = 0x5c0f;
        wchar_t j = 0x5c0f;

        STF_ASSERT_EQ(i, j);
    }
    else
    {
        wchar_t i = 0x00005c0f;
        wchar_t j = 0x00005c0f;

        STF_ASSERT_EQ(i, j);
    }
}
