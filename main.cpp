#include <iostream>
#include <ctime>
#include <vector>
#include <memory>

#include "include/data.hpp"


int main()
{
	std::time_t t = time(nullptr);
	std::tm *t_str = std::localtime(&t);

	std::vector<std::unique_ptr<gym::simulator::Equipment>> database;

	t = time(nullptr);
	t_str = std::localtime(&t);
	database.push_back(std::make_unique<gym::simulator::Dumbells>("Гантели до 12 кг.", 120.2, *t_str));

	t = time(nullptr);
	t_str = std::localtime(&t);
	database.push_back(std::make_unique<gym::simulator::Other>("Коврик для йоги", 30.99, *t_str));

	t = time(nullptr);
	t_str = std::localtime(&t);
	database.push_back(std::make_unique<gym::simulator::ExersizeMachine>
			("Комплекс блоков", "Спина" , 1000, *t_str));

	for (auto ptr = database.begin(); ptr != database.end(); ptr++)
	{
		std::cout << *(ptr->get());
	}

	return 0;
}
