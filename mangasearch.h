#ifndef MANGASEARCH_H
#define MANGASEARCH_H

#include "manga.h"

#include <string>
#include <vector>

class MangaSearch
{
public:
    std::vector<Manga> search(const std::string& Query);
};

#endif