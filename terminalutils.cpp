#include "terminalutils.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#endif

TerminalSize TerminalUtils::getSize()
{
    TerminalSize Size{80, 24};

#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO Info;

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info))
    {
        Size.Columns = Info.srWindow.Right - Info.srWindow.Left + 1;
        Size.Rows = Info.srWindow.Bottom - Info.srWindow.Top + 1;
    }
#else
    struct winsize WindowSize;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &WindowSize) == 0)
    {
        Size.Columns = WindowSize.ws_col;
        Size.Rows = WindowSize.ws_row;
    }
#endif

    return Size;
}

int TerminalUtils::readKey()
{
#ifdef _WIN32
    int Key = _getch();

    if (Key == 0 || Key == 224)
    {
        Key = _getch();
    }

    return Key;
#else
    struct termios OldSettings;
    struct termios NewSettings;

    tcgetattr(STDIN_FILENO, &OldSettings);
    NewSettings = OldSettings;
    NewSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &NewSettings);

    int Key = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &OldSettings);

    return Key;
#endif
}