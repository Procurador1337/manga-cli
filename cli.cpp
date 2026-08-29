#include "cli.h"
#include "pageviewer.h"
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

    int Offset = 0;
    int Total = 0;
    std::vector<Chapter> ChapterResults;
    int ChapterChoice = 0;

    while (true)
    {
        ChapterResults =
            ChapterSearcher.search(SelectedManga, Offset, Total);

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

        bool HasNextPage =
            (Offset + static_cast<int>(ChapterResults.size())) < Total;

        int NextPageOption =
            static_cast<int>(ChapterResults.size()) + 1;

        if (HasNextPage)
        {
            std::cout
                << NextPageOption
                << ". Next page\n";
        }

        std::cout << '\n';

        int MaxChoice =
            HasNextPage ? NextPageOption : static_cast<int>(ChapterResults.size());

        ChapterChoice = Selector.getChoice(MaxChoice);

        if (HasNextPage && ChapterChoice == NextPageOption)
        {
            Offset += static_cast<int>(ChapterResults.size());
            continue;
        }

        break;
    }

    Chapter SelectedChapter =
        ChapterResults[ChapterChoice - 1];

    std::cout << "\nSelected:\n";
    std::cout << "Manga: "
              << SelectedManga.getName()
              << '\n';

    std::cout << "Chapter: "
              << SelectedChapter.getName()
              << '\n';

    PageViewer Viewer;
    Viewer.view(SelectedChapter.getID());

    return 0;
}
