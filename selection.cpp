#include "selection.h"

#include <iostream>
#include <limits>

int Selection::getChoice(int Maximum)
{
    int Choice;

    while (true)
    {
        std::cout << "Select an option: ";

        if (std::cin >> Choice &&
            Choice >= 1 &&
            Choice <= Maximum)
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
                );

            return Choice;
        }

        std::cout << "Invalid selection. Try again.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
            );
    }
}