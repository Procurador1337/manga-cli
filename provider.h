#ifndef PROVIDER_H
#define PROVIDER_H

#include "manga.h"
#include "chapter.h"

#include <string>
#include <vector>

class Provider
{
public:
    std::vector<Manga> searchManga(const std::string& Query);

    std::vector<Chapter> getChapters(
        const std::string& MangaID
        );

    std::vector<Chapter> getChapters(
        const std::string& MangaID,
        int Offset,
        int& OutTotal
        );

    std::vector<std::string> getPageURLs(const std::string& ChapterID);

    int getChapterCount(const std::string& MangaID);

    std::vector<Manga> searchManga(const std::string& Query, const std::string& Language);
    std::vector<Chapter> getChapters(const std::string& MangaID, int Offset, int& OutTotal, const std::string& Language);
    int getChapterCount(const std::string& MangaID, const std::string& Language);
};

#endif