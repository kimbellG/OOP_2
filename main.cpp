#include <iostream>
#include <ctime>
#include <vector>
#include <memory>

#ifdef WIN32
#include <windows.h>
#endif

#include "include/gym.hpp"
#include "include/eqinterface.h"
#include "include/consolemanipulator.h"
#include "include/get_fromkb.hpp"
#include "include/menu_func.hpp"
#include "include/eqinterface.h"

std::string input_name()
{
	std::string name;
	gym::input_interface::clear_buf();
	std::getline(std::cin, name);
	return name;
}

void term_handle()
{
	std::cout << "My handle" << std::endl;
	std::cout << "closing program";
	gym::input_interface::pause();
	exit(1);
}

void (*std_term)() = std::set_terminate(term_handle);

bool is_current_test_entry(const std::string &str, const std::string value);

void test_entrys(std::vector<std::string> strs, std::vector<std::string> values)
{
    if (strs.size() != values.size())
    {
        throw std::invalid_argument("test_entrys: strs != values");
    }

    try
    {
        for (auto str = strs.begin(), value = values.begin(); str != strs.end() || value != values.end(); str++, value++)
        {
           if (!is_current_test_entry(*str, *value))
           {
               throw std::runtime_error(std::string(*str + " != " + *value).c_str());
            }
        }
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "end of test!" << std::endl;
    std::exit(0);
}

bool is_current_test_entry(const std::string &str, const std::string value)
{
    std::string result = gym::input_interface::get_eq_name_from_file_entry(str);
    return result == value;
}


int main()
{
#ifdef WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    std::vector<std::string> strs = {"abc:zxc:asd", "qwe"};
    std::vector<std::string> values = {"abc", "qwe"};

    test_entrys(strs, values);

 	gym::Gym *mainbase_ptr;

	try
	{
		mainbase_ptr = new gym::Gym;
	}
	catch (std::bad_alloc &)
	{
		std::cout << "Bad alloc";
		gym::input_interface::pause();
		mainbase_ptr = ::new gym::Gym;
	}

	gym::Gym &mainbase = *mainbase_ptr;

//	throw std::logic_error("generate handle");

	enum menu_p
	{
		add = 1,
		del,
		find,
		out,
		edit,
		qa,
		exit
	};

	int choice;
	while (true)
	{
		gym::input_interface::clear_window();
		std::cout << "Complex work with your collection of simulators: " << std::endl
			<< "\t\tTotal cost: " << mainbase.total_cost() << std::endl
			<< "\t1. Add new simulator." << std::endl
			<< "\t2. Delete simulator." << std::endl
			<< "\t3. Find simulator for name." << std::endl
			<< "\t4. See all simulator." << std::endl
			<< "\t5. Edit trainers." << std::endl
			<< "\t6. Question." << std::endl
			<< "\t7. Exit." << std::endl;

			std::cout << "Input your choice: ";
		try {
			choice = get_from_keyboard<int>();
		} catch (std::runtime_error &e) {
			std::cout << e.what();
			gym::input_interface::pause();
			continue;
		}

		if (choice < 1 || choice > 6)
		{
			std::cout << "\nIncorrect choice";
			gym::input_interface::pause();	
			continue;
		}

		std::string name;
		switch (choice)
		{
			case add:
				gym::input_interface::clear_window();
				std::cout << "Input name: ";
				name = input_name();

				try
				{
					mainbase.create_eq(name);
				}
				catch (std::invalid_argument &)
				{
					gym::input_interface::pause();
					continue;
				}
				
				break;

			case del:
				gym::input_interface::clear_window();
				std::cout << "Input name for delete: ";
				name = input_name();
				try
				{
					mainbase.delete_eq(name);
				}
				catch (std::invalid_argument &)
				{
					gym::input_interface::pause();
					continue;
				}

				break;

			case find:
				gym::input_interface::clear_window();
				std::cout << "Input name for search: ";
				name = input_name();
				try
				{
					mainbase.find(name);
				}
				catch (std::out_of_range &)
				{
					gym::input_interface::pause();
					continue;
				}

				break;

			case out:
				gym::input_interface::clear_window();
				std::cout << mainbase << std::endl;

				gym::input_interface::clear_buf();
				std::cin.get();

				break;

			case edit:
				gym::input_interface::clear_window();
				std::cout << mainbase << std::endl;

				mainbase.edit();

				break;
		case qa:
			gym::input_interface::clear_window();
            inputAndAnswerQ();

			gym::input_interface::pause();
            break;

			case exit:
				delete mainbase_ptr;
				return 0;
		}
	}

	delete mainbase_ptr;
	return 0;
}
