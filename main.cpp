#include <iostream>
#include <ctime>

#include "include/classes.hpp"


int main()
{
	std::time_t t = time(nullptr);
	std::tm *t_str = std::localtime(&t);
	gym::simulator::Dumbells test("Гантели до 12 кг.", 120.2, *t_str);

	std::cout << test << std::endl;

	return 0;
}
