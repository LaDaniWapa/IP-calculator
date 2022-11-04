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

void title(string title) {
	SetConsoleTitleA(title);
}

#else
#include <stdlib.h>
#include <strings.h>

using namespace std;

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
	cout << ("\033[1;" + to_string((int)c) + "m");
} // \x1b or \033 ?

void clear() {
	system("clear");
}

void title(string title) {
	string cmd = "echo '\\033]0;" + title + "\\a'";
	system(cmd.c_str());
}

#endif