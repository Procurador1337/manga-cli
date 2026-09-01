#include "chaptersearch.h"
#include "provider.h"

std::vector<Chapter> ChapterSearch::search(const Manga& SelectedManga, int Offset, int& OutTotal, const std::string& Language)
{
    Provider ProviderClient;

    return ProviderClient.getChapters(SelectedManga.getID(), Offset, OutTotal, Language);
}