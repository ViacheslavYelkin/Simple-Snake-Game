#include <iostream>
#include <windows.h>

#include "Console.h"

// This code for working with console properties was borrowed on Stack Overflow
// Thanks to Cameron, Captain Obvlious and herohuyongtao

void Console::cleanConsole()
{
    static const HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD top_left = { 0, 0 };

    std::cout.flush();

    GetConsoleScreenBufferInfo(h_out, &csbi);

    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

    DWORD written;

    FillConsoleOutputCharacter(h_out, TEXT(' '), length, top_left, &written);
    FillConsoleOutputAttribute(h_out, csbi.wAttributes, length, top_left, &written);
    SetConsoleCursorPosition(h_out, top_left);
}

void Console::setCursorPosition(int x, int y)
{
    static const HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(h_out, coord);
}

void Console::makeCursorInvisible()
{
    HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cur_info;
    GetConsoleCursorInfo(h_out, &cur_info);
    cur_info.bVisible = FALSE;
    SetConsoleCursorInfo(h_out, &cur_info);
}

void Console::getConsoleSize(int& rows, int& columns)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(h_out, &csbi);
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
