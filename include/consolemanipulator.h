#ifndef CONSOLEMANIPULATOR_H
#define CONSOLEMANIPULATOR_H


#include <iostream>
#include <iomanip>
#include <windows.h>
#include <cmath>
#include <string>
#include <vector>
#include <conio.h>

class ConsoleManipulator {
	static const short down = 80;
	static const short up = 72;
	static const short leftarr = 75;
	static const short rightarr = 77;

	std::vector<size_t> stepx;
	size_t stepy;

	HANDLE cmd;

public:
	ConsoleManipulator(const std::vector<size_t> &stepx, const size_t stepy);

	COORD GetConsoleCursorPosition();
	void clear_window(COORD start, const size_t strnum = 10);
	void backspace() {
		COORD curr = GetConsoleCursorPosition();
		curr.X--;
		printf(" ");
		SetConsoleCursorPosition(curr);
		printf(" ");
		SetConsoleCursorPosition(curr);
	}

	static std::string gettab(const size_t size, const char c = ' ');

	void SetConsoleCursorPosition(COORD coord) {
		::SetConsoleCursorPosition(cmd, coord);
	}

	void mvtable(size_t &index, size_t &field, COORD &pos, const size_t size, const size_t numfield);

};

#endif // CONSOLEMANIPULATOR_H
