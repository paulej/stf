/*
 *  integral_array.h
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      STF adapter to facilitate dumping an std::array holding integral types
 *      as hex when STF comparisons like STF_ASSERT_EQ fail.
 *
 *      Output adapters MUST be included before stf.h.
 *
 *  Portability Issues:
 *      None.
 */

#pragma once

#include <ostream>
#include <iomanip>
#include <sstream>
#include <array>
#include <cstddef>
#include <type_traits>

// Define output stream operator to support dumping std::array types has hex
template<typename T,
         std::size_t N,
         typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
std::ostream &operator<<(std::ostream &o, const std::array<T, N> &array)
{
    std::ostringstream oss;

    oss << std::hex << std::setfill('0') << "0x";

    for (std::size_t i = 0; i < array.size(); i++)
    {
        if (i) oss << " ";
        oss << std::setw(sizeof(T) * 2) << +array[i];
    }

    return o << oss.str();
}
