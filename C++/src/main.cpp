/*
  RMIT University Vietnam
  Course: EEET2482/COSC2082 Advanced Programming Techniques
  Semester: 2023-3
  Assignment: Final Group Project
  Author: Trinh Nguyen Ha (s3981134)
  Compiler used: g++ (MinGW.org GCC-6.3.0-1) 6.3.0
  Created date: 25/12/2023
  Last modified: 02/01/2024
  Acknowledgement: https://superuser.com/questions/413073/windows-console-with-ansi-colors-handling
*/

#include <iostream>
#include <string>
#include "TimeBankSystem.h"
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

using std::cin;
using std::cout;

void enableANSIColors()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return;
    }
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return;
    }
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

int main()
{
// Enable ANSI colors on Windows
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
    enableANSIColors();
    // Set the console to UTF-8
    SetConsoleOutputCP(CP_UTF8); // Print out special UTF-8 characters

#endif

    TimeBankSystem sys;
    sys.loadData();
    sys.automaticallyUpdate();
    sys.welcomeScreen();
    sys.systemMenu();
    sys.updateRatings();
    sys.saveData();
    sys.clearData();

    return 0;
}