/*
 *  some_objects.cpp
 *
 *  Copyright (C) 2023
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved
 *
 *  Description:
 *      This just defines two related dummy objects used for testing
 *      comparison operations.
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
    o << "SomeObject{" << object.GetValue() << "}";

    return o;
}

class SomeOtherObject : public SomeObject
{
    using SomeObject::SomeObject;
};

std::ostream &operator<<(std::ostream &o, const SomeOtherObject &object)
{
    o << "SomeOtherObject{" << object.GetValue() << "}";

    return o;
}

class SomeNewObject
{
    public:
        SomeNewObject(unsigned value) : value(value)
        {
            // Nothing to do
        };
        ~SomeNewObject() = default;
        unsigned GetValue() const { return value; }

        bool operator==(const SomeNewObject &other) const
        {
            return value == other.value;
        }

        bool operator!=(const SomeNewObject &other) const
        {
            return !(value == other.value);
        }

        bool operator>(const SomeNewObject &other) const
        {
            return value > other.value;
        }

        bool operator>=(const SomeNewObject &other) const
        {
            return value >= other.value;
        }

        bool operator<(const SomeNewObject &other) const
        {
            return value < other.value;
        }

        bool operator<=(const SomeNewObject &other) const
        {
            return value <= other.value;
        }

    protected:
        unsigned value;
};

std::ostream &operator<<(std::ostream &o, const SomeNewObject &object)
{
    o << "SomeNewObject{" << object.GetValue() << "}";

    return o;
}
