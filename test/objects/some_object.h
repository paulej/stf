/*
 *  some_objects.cpp
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      This just implements a dummy object use for testing comparison
 *      operations.
 *
 *  Portability Issues:
 *      None.
 */

#pragma once

#include <iostream>

class SomeObject
{
    public:
        SomeObject(unsigned value) : value(value)
        {
            // Nothing to do
        };
        ~SomeObject() = default;
        unsigned GetValue() const { return value; }

        bool operator==(const SomeObject &other) const
        {
            return value == other.value;
        }

        bool operator!=(const SomeObject &other) const
        {
            return !(value == other.value);
        }

        bool operator>(const SomeObject &other) const
        {
            return value > other.value;
        }

        bool operator>=(const SomeObject &other) const
        {
            return value >= other.value;
        }

        bool operator<(const SomeObject &other) const
        {
            return value < other.value;
        }

        bool operator<=(const SomeObject &other) const
        {
            return value <= other.value;
        }


    protected:
        unsigned value;
};

std::ostream &operator<<(std::ostream &o, const SomeObject &object)
{
    o << "Object{" << object.GetValue() << "}";

    return o;
}
