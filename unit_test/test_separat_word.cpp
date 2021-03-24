#include <vector>
#include <string>
#include <stdexcept>

#include "unit_test.hpp"
#include "../include/eqinterface.h"
#include "../include/procesing_entry.hpp"


namespace test_unit
{
    TestEntryInterface::TestEntryInterface(std::vector<std::string> strs, std::vector<std::string> values, std::ostream &out)
        : __strs(strs), __values(values), __count_success(0), __count_failure(0), __out(out)
    {
    }

    void TestEntryInterface::test_entrys_name()
    {
        if (__strs.size() != __values.size())
        {
            throw std::invalid_argument("test_entrys: strs != values");
        }


            for (auto str = __strs.begin(), value = __values.begin(); str != __strs.end(); str++, value++)
            {
                try
                {
                   if (!is_current_test_entry(*str, *value))
                   {
                       throw std::runtime_error(std::string(*str + " != " + *value).c_str());
                   }
                   ++__count_success;
               }
               catch (std::runtime_error &e)
               {
                   std::cerr << e.what() << std::endl;
                   ++__count_failure;
               }


            }

        print_result();
        std::cout << "end of test!" << std::endl;
        std::exit(0);
    }

    void TestEntryInterface::print_result()
    {
        __out << "TEST:\t" << "SUCCESS: " << __count_success << " | " << "FAILURE: " << __count_failure << std::endl;
    }
}




