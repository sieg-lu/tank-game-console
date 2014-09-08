#ifndef __CONSOLE_API_H__
#define __CONSOLE_API_H__

#include <windows.h>
#include <stdio.h>

// Direct console output
void ConsolePrint(char *CharBuffer, int len);

// Direct Console output at a particular coordinate.
void ConsolePrintAt(int x, int y, char *CharBuffer, int len);

// This will set the position of the cursor
void GotoXY(int x, int y);

// This will clear the console.
void ClearConsole();

// This will clear the console while setting the foreground and
// background colors.
void ClearConsoleToColors(int ForgC, int BackC);

// This will set the foreground and background color for printing in a console window.
void SetColorAndBackground(int ForgC, int BackC);

// This will set the foreground color for printing in a console window.
void SetColor(int ForgC);

// Hides the console cursor
void HideCursor();

// Shows the console cursor
void ShowCursor();

#endif ///> end of __CONSOLE_API_H__