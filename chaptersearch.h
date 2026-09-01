#ifndef CHAPTERSEARCH_H
#define CHAPTERSEARCH_H

#include "chapter.h"
#include "manga.h"

#include <vector>

class ChapterSearch
{
public:
    std::vector<Chapter> search(const Manga& SelectedManga);
    std::vector<Chapter> search(const Manga& SelectedManga, int Offset, int& OutTotal);
    std::vector<Chapter> search(const Manga& SelectedManga, int Offset, int& OutTotal, const std::string& Language);
};

#endif