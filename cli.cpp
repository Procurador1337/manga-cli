#include "cli.h"
#include "mangasearch.h"
#include "chaptersearch.h"
#include "selection.h"
#include "pageviewer.h"

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

    if (MangaResults.empty())
    {
        std::cout
            << "\nNo manga found for \""
            << MangaName
            << "\".\n";

        return 1;
    }

    std::cout << "\nResults:\n\n";

    for (std::size_t Index = 0;
         Index < MangaResults.size();
         ++Index)
    {
        std::cout
            << Index + 1
            << ". "
            << MangaResults[Index].getName()
            << " ("
            << MangaResults[Index].getChapterCount()
            << " chapters)\n";
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

        if (ChapterResults.empty())
        {
            std::cout
                << "\nNo chapters found for \""
                << SelectedManga.getName()
                << "\".\n";

            return 1;
        }

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

    int LocalIndex = ChapterChoice - 1;

    while (true)
    {
        std::cout << "\nSelected:\n";
        std::cout << "Manga: "
                  << SelectedManga.getName()
                  << '\n';

        std::cout << "Chapter: "
                  << SelectedChapter.getName()
                  << '\n';

        PageViewer Viewer;
        Viewer.view(SelectedChapter.getID());

        bool HasNext = false;
        Chapter NextChapter("", "");

        if (LocalIndex + 1 < static_cast<int>(ChapterResults.size()))
        {
            HasNext = true;
            NextChapter = ChapterResults[LocalIndex + 1];
            LocalIndex = LocalIndex + 1;
        }
        else if (Offset + static_cast<int>(ChapterResults.size()) < Total)
        {
            int NewOffset =
                Offset + static_cast<int>(ChapterResults.size());
            int NewTotal = 0;

            std::vector<Chapter> NextPageResults =
                ChapterSearcher.search(SelectedManga, NewOffset, NewTotal);

            if (!NextPageResults.empty())
            {
                Offset = NewOffset;
                Total = NewTotal;
                ChapterResults = NextPageResults;
                LocalIndex = 0;
                HasNext = true;
                NextChapter = ChapterResults[0];
            }
        }

        if (!HasNext)
        {
            std::cout << "\nNo more chapters.\n";
            break;
        }

        std::cout
            << "\nContinue to \""
            << NextChapter.getName()
            << "\"? (y/n): ";

        std::string Response;
        std::getline(std::cin, Response);

        if (Response.empty() ||
            (Response[0] != 'y' && Response[0] != 'Y'))
        {
            break;
        }

        SelectedChapter = NextChapter;
    }

    return 0;
}