#ifndef UNIT_TEST_HPP
#define UNIT_TEST_HPP

#include <iostream>
#include <vector>
#include <string>

#include "../include/eqinterface.h"
#include "../include/procesing_entry.hpp"

namespace test_unit
{
    class TestEntryInterface
    {
        std::vector<std::string> __strs;
        std::vector<std::string> __values;

        int __count_success;
        int __count_failure;

        std::ostream &__out;
    public:
        TestEntryInterface(std::vector<std::string> strs, std::vector<std::string> values, std::ostream &out = std::cout);

        void test_entrys_name();
        virtual bool is_current_test_entry(const std::string &str, const std::string &value) = 0;
        virtual void run() = 0;

        void print_result();
    };

    class TestNameEntry
            : public TestEntryInterface
    {
    public:
        TestNameEntry(std::vector<std::string> strs, std::vector<std::string> values)
            : TestEntryInterface(strs, values) {}

        bool is_current_test_entry(const std::string &str, const std::string &value) override
        {
            std::string result = gym::input_interface::get_eq_name_from_file_entry(str);
            std::cout << result << std::endl;
            return result == value;
        }

    };

    class TestSeparatingWord
            : public TestEntryInterface
    {
        int __number;
    public:
        TestSeparatingWord(std::vector<std::string> strs, std::vector<std::string> values, int number)
            : TestEntryInterface(strs, values), __number(number)
        {
        }

        bool is_current_test_entry(const std::string &str, const std::string &value) override
        {
            std::string result = gym::input_interface::get_word_by_separator(str, __number);
            return result == value;
        }

        void run() override
        {
            std::vector<std::string> strs = {"abc:zxc:asd", "qwe:lnb", "abc:cde:qwerty"};
            std::vector<std::string> values = {"zxc", "lnb", "cde"};
            test_unit::TestSeparatingWord test(strs, values, 1);
            test.test_entrys_name();
        }
    };
}
#endif // UNIT_TEST_HPP
