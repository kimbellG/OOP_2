#ifndef GET_NUMBER_H
#define GET_NUMBER_H

#include <iostream>
#include <iomanip>
#include <climits>

namespace range_t
{
    enum Types_Range
    {
        SHORT = 5,
        USHORT = 5,
        INT = 10,
        UINT = 10,
        LONG = 10,
        ULONG = 10,
        FLOAT = 10,
        DOUBLE = 19,
        ERR = -1,
    };
}


template <class T = const char> std::int16_t get_range(T type)
{
    switch (type)
    {
        case 's': return range_t::SHORT; break;
        case 't': return range_t::USHORT; break;
        case 'i': return range_t::INT; break;
        case 'j': return range_t::UINT; break;
        case 'l': return range_t::LONG; break;
        case 'm': return range_t::ULONG; break;
        case 'y': return range_t::ULONG; break;
        case 'f': return range_t::FLOAT; break;
        case 'd': return range_t::DOUBLE; break;
    }

    return range_t::ERR;
}

template <class T>
void getnumber(T& number)
{
    std::int16_t max_length = get_range(typeid(T).name()[0]);

    if (max_length == range_t::ERR)
        throw std::runtime_error("Invalid type");

    std::cin >> std::setw(max_length) >> number;

    if (std::cin.fail())
    {
//      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.clear();
        throw std::runtime_error("Invalid number");
    }
    else
    {
  //      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.gcount() > 1)
            throw std::runtime_error("Invalid number");
    }
}


#endif // GET_NUMBER_H
