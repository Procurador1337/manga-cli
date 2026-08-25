#include "cli.h"
#include "mangasearch.h"
#include "chaptersearch.h"
#include "selection.h"

#include <iostream>
#include <string>
#include <vector>

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

    MangaSearch MangaSearcher;
    Selection Selector;

    std::vector<Manga> MangaResults =
        MangaSearcher.search(MangaName);

    std::cout << "\nResults:\n\n";

    for (std::size_t Index = 0;
         Index < MangaResults.size();
         ++Index)
    {
        std::cout
            << Index + 1
            << ". "
            << MangaResults[Index].getName()
            << '\n';
    }

    std::cout << '\n';

    int MangaChoice =
        Selector.getChoice(
            static_cast<int>(MangaResults.size())
            );

    Manga SelectedManga =
        MangaResults[MangaChoice - 1];

    ChapterSearch ChapterSearcher;

    std::vector<Chapter> ChapterResults =
        ChapterSearcher.search(SelectedManga);

    std::cout << "\n"
              << SelectedManga.getName()
              << " Chapters:\n\n";

    for (std::size_t Index = 0;
         Index < ChapterResults.size();
         ++Index)
    {
        std::cout
            << Index + 1
            << ". "
            << ChapterResults[Index].getName()
            << '\n';
    }

    std::cout << '\n';

    int ChapterChoice =
        Selector.getChoice(
            static_cast<int>(ChapterResults.size())
            );

    Chapter SelectedChapter =
        ChapterResults[ChapterChoice - 1];

    std::cout << "\nSelected:\n";
    std::cout << "Manga: "
              << SelectedManga.getName()
              << '\n';

    std::cout << "Chapter: "
              << SelectedChapter.getName()
              << '\n';

    return 0;
}