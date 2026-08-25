#include "chaptersearch.h"

std::vector<Chapter> ChapterSearch::search(const Manga&)
{
    std::vector<Chapter> Results;

    Results.emplace_back("chapter-1", "Chapter 1");
    Results.emplace_back("chapter-2", "Chapter 2");
    Results.emplace_back("chapter-3", "Chapter 3");
    Results.emplace_back("chapter-4", "Chapter 4");
    Results.emplace_back("chapter-5", "Chapter 5");

    return Results;
}