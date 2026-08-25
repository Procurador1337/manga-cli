#include "cli.h"

#include <QCoreApplication>

int main(int argc, char* argv[])
{
    QCoreApplication Application(argc, argv);

    CLI cli;

    return cli.run();
}