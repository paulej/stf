/*
 *  integral_vector.h
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      STF adapter to facilitate dumping an std::vector holding integral types
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
#include <vector>
#include <cstddef>
#include <type_traits>

// Define output stream operator to support dumping std::vector types has hex
template<typename T,
         typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
std::ostream &operator<<(std::ostream &o, const std::vector<T> &vec)
{
    std::ostringstream oss;

    oss << std::hex << std::setfill('0') << "0x";

    for (std::size_t i = 0; i < vec.size(); i++)
    {
        if (i) oss << " ";
        oss << std::setw(sizeof(T) * 2) << +vec[i];
    }

    return o << oss.str();
}
