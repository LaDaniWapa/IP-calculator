#pragma once
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <Windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

enum class Colors {
	Blue = 9,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White
};

void change_output_color(Colors c) {
	SetConsoleTextAttribute(hConsole, (WORD)c);
}


void clear() {
	system("cls");
}


void pause() {
	change_output_color(Colors::White);
	system("pause");
}

#else
#include <stdlib.h>

enum class Colors {
	Red = 31,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	White,
};

void change_output_color(Colors c) {
	std::cout << ("\033[1;" + std::to_string((int)c) + "m");
} // \x1b or \033 ?

void clear() {
	system("clear");
}

void pause() {
	change_output_color(Colors::White);
	cout << "Press any key to continue . . ." << endl;
	cin.get();
}

#endif