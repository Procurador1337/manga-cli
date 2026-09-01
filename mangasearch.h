#ifndef MANGASEARCH_H
#define MANGASEARCH_H

#include "manga.h"

#include <string>
#include <vector>

class MangaSearch
{
public:
    std::vector<Manga> search(const std::string& Query);
    std::vector<Manga> search(const std::string& Query, const std::string& Language);
};

#endif