#ifndef TERMINALUTILS_H
#define TERMINALUTILS_H

struct TerminalSize
{
    int Columns;
    int Rows;
};

class TerminalUtils
{
public:
    static TerminalSize getSize();
    static int readKey();
};

#endif