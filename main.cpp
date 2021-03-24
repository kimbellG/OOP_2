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
#include "unit_test/unit_test.hpp"

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

int main()
{
#ifdef WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    std::string filename = get_filename();
 	gym::Gym *mainbase_ptr;

	try
	{
        mainbase_ptr = new gym::Gym(filename);
	}
	catch (std::bad_alloc &)
	{
		std::cout << "Bad alloc";
        gym::input_interface::pause();
        mainbase_ptr = ::new gym::Gym(filename);
	}

	gym::Gym &mainbase = *mainbase_ptr;
    mainbase.load_equipment_from_file();

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

        if (choice < 1 || choice > 7)
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
				
                mainbase.save_equipment_to_file();
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

                mainbase.save_equipment_to_file();
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
                mainbase.save_equipment_to_file();

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


	return 0;
}
