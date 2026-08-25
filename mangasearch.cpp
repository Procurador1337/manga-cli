#include "mangasearch.h"
#include "provider.h"

std::vector<Manga> MangaSearch::search(const std::string& Query)
{
    Provider ProviderClient;

    return ProviderClient.searchManga(Query);
}