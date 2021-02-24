#include <iostream>
#include <ctime>
#include <vector>
#include <memory>
#include <windows.h>

#include "include/data.hpp"

int main()
{
#ifdef WIN32
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
#endif
	std::time_t t = time(nullptr);
	std::tm *t_str = std::localtime(&t);

	std::vector<std::unique_ptr<gym::simulator::Equipment>> database;

	t = time(nullptr);
	t_str = std::localtime(&t);
	database.push_back(std::make_unique<gym::simulator::Dumbells>("Dumbells before 12 kg.", 120.2, *t_str));

	t = time(nullptr);
	t_str = std::localtime(&t);
	database.push_back(std::make_unique<gym::simulator::Other>("Palace", 30.99, *t_str));

	t = time(nullptr);
	t_str = std::localtime(&t);
	database.push_back(std::make_unique<gym::simulator::ExersizeMachine>
			("Complex blocks" , "Back", 1000, *t_str));

	database[0]->print_header(std::cout);
	for (auto ptr = database.begin(); ptr != database.end(); ptr++)
	{
		std::cout << *(ptr->get());
	}
	database[0]->print_footer(std::cout);

	return 0;
}
