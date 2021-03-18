#ifndef __GET_FROM_KB__
#define __GET_FROM_KB__

#include <iostream>

bool is_empty_cin();
char get_last_symbol_cin();
void proccesingCinError();

template <typename T> inline T get_from_keyboard() {
	T valueFromKeyboard;
	std::cin >> valueFromKeyboard;

	proccesingCinError();
	
	return valueFromKeyboard;
}

void proccesingCinError() {
	
	if (std::cin.fail()) {
		std::cin.ignore(100, '\n');
		throw std::runtime_error("Incorrect input");
	} 

	if (is_empty_cin()) {
		std::cin.ignore(100, '\n');
		throw std::runtime_error("Incorrect input");
	}
}


bool is_empty_cin() {
	char last_symbol = get_last_symbol_cin();

	return last_symbol != '\n';
}

char get_last_symbol_cin() {
	return std::cin.peek();
}


#endif
