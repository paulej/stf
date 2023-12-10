/*
 *  test_adapters.cpp
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      Module to exercise tests that, if they were to fail, would utilize
 *      the include adapters to produce more useful output.
 *
 *  Portability Issues:
 *      None.
 */

#include <array>
#include <vector>
#include <stf/adapters/integral_array.h>
#include <stf/adapters/integral_vector.h>
#include <stf/stf.h>

// Test integral array adapter
STF_TEST(Adapters, IntegralArrays)
{
    const std::array<std::uint8_t, 16> array_1 =
    {
        0xa4, 0x4a, 0x82, 0x66, 0xee, 0x1c, 0x8e, 0xb0,
        0xc8, 0xb5, 0xd4, 0xcf, 0x5a, 0xe9, 0xf1, 0x9a
    };
    std::array<std::uint8_t, 16> array_2;

    array_2 = array_1;

    STF_ASSERT_EQ(array_1, array_2);
}

// Test integral vector adapter
STF_TEST(Adapters, IntegralVector)
{
    const std::vector<std::uint8_t> vec_1 =
    {
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    };
    std::vector<std::uint8_t> vec_2;

    vec_2 = vec_1;

    STF_ASSERT_EQ(vec_1, vec_2);
}
