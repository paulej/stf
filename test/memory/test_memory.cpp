/*
 *  test_memory.cpp
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      Module to exercise tests related to memory comparisons using the Simple
 *      Test Framework library.  It also does comparisons between pointers.
 *
 *  Portability Issues:
 *      None.
 */

#include <cstring>
#include <cstdint>
#include <stf/stf.h>

STF_TEST(Memory, Test1)
{
    const std::uint8_t c_array1[] = { 0x01, 0x02, 0x08, 0x04 };
    const std::uint8_t c_array2[] = { 0x01, 0x02, 0x08, 0x04 };

    STF_ASSERT_MEM_EQ(c_array1, c_array2, sizeof(c_array1));
}

STF_TEST(Memory, Test2)
{
    const std::uint8_t c_array1[] = { 0x01, 0x02, 0x08, 0x04 };
    const std::uint8_t c_array2[] = { 0x01, 0x02, 0x08, 0x05 };

    STF_ASSERT_MEM_NE(c_array1, c_array2, sizeof(c_array1));
}

STF_TEST(Memory, Test3)
{
    char buffer1[100];
    char buffer2[100];

    // Ensure the buffers are the same size
    STF_ASSERT_EQ(sizeof(buffer1), sizeof(buffer2));

    // Clear the memory
    std::memset(buffer1, 0, 100);
    std::memset(buffer2, 0, 100);

    buffer1[50] = 'a';
    buffer2[50] = 'a';

    STF_ASSERT_MEM_EQ(buffer1, buffer2, sizeof(buffer1));
}

STF_TEST(Memory, Test4)
{
    int i = 0;
    int *j = &i;
    int *k = &i;

    STF_ASSERT_EQ(j, k);
}

STF_TEST(Memory, Test5)
{
    int i = 0;
    int j = 0;
    int *k = &i;
    int *l = &j;

    STF_ASSERT_NE(k, l);
}

STF_TEST(Memory, Test6)
{
    std::uint8_t q[20];
    std::uint8_t *p = nullptr;

    STF_ASSERT_NE(p, q);

    p = q;

    STF_ASSERT_EQ(p, q);
}
