#include "consolemanipulator.h"

ConsoleManipulator::ConsoleManipulator(const std::vector<size_t> &stpx, const size_t stpy) : stepx(stpx), stepy(stpy) {
	cmd = GetStdHandle(STD_OUTPUT_HANDLE);
}


COORD ConsoleManipulator::GetConsoleCursorPosition() {
	  CONSOLE_SCREEN_BUFFER_INFO cbsi;
	  if (GetConsoleScreenBufferInfo(cmd, &cbsi)) {
		  return cbsi.dwCursorPosition;
	  }
	  else {
		  // The function failed. Call GetLastError() for details.
		  COORD invalid = { 0, 0 };
		  return invalid;
	  }
}

void ConsoleManipulator::clear_window(COORD start, const size_t strnum) {
	SetConsoleCursorPosition(start);
	for (size_t i = 0; i < strnum * 3; i++) {
		for (size_t j = 0; j < 170; j++)
			std::cout << ' ';
		std::cout << std::endl;
	}
	SetConsoleCursorPosition(start);
}

std::string ConsoleManipulator::gettab(const size_t size, const char c) {
		std::string tab;
		for (int i = 0; i < log(size) / log(10) + 1; i++)
			tab.push_back(c);
		return tab;
}

void ConsoleManipulator::mvtable(size_t &index, size_t &field, COORD &pos, const size_t size, const size_t numfield) {
		COORD start = GetConsoleCursorPosition();
		clear_window(start, 1);
		SetConsoleCursorPosition(pos);

		int arrow = '\0';

		do {
			if (arrow == 224) {
				switch (arrow = getch()) {

				case down: // down
					if (index < size - 1) {
						index++;
						pos.Y += stepy;
					}
					break;

				case up: // up
					if (index > 0) {
						index--;
						pos.Y -= stepy;
					}
					break;

				case leftarr: // left
					if (field > 0) {
						pos.X -= stepx[field];
						field--;
					}
					break;

				case rightarr: //right
					if (field < numfield - 1) {
						field++;
						pos.X += stepx[field];
					}
					break;
				}
			}

			SetConsoleCursorPosition(pos);

		} while ((arrow = getch()) != '\r');

		SetConsoleCursorPosition(start);
}
