#pragma once

class Console {
public:

	static void cleanConsole();
	static void setCursorPosition(int x, int y);
	static void makeCursorInvisible();
	static void getConsoleSize(int& rows, int& columns);
};