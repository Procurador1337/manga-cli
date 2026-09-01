#include "mangasearch.h"
#include "provider.h"

std::vector<Manga> MangaSearch::search(const std::string& Query, const std::string& Language)
{
    Provider ProviderClient;

    return ProviderClient.searchManga(Query, Language);
}