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
};

#endif