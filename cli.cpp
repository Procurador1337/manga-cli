#include "cli.h"
#include "manga.h"

#include <iostream>
#include <string>

int CLI::run()
{
    std::string MangaName;

    std::cout << "Manga CLI\n\n";
    std::cout << "Enter manga name: ";

    std::getline(std::cin, MangaName);

    if (MangaName.empty())
    {
        std::cout << "No manga name entered.\n";
        return 1;
    }

    Manga SelectedManga(MangaName);

    std::cout << "\nSearching for: "
              << SelectedManga.getName()
              << '\n';

    return 0;
}