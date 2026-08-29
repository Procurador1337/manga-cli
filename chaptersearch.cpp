#include "chaptersearch.h"
#include "provider.h"

std::vector<Chapter> ChapterSearch::search(const Manga& SelectedManga)
{
    Provider ProviderClient;

    return ProviderClient.getChapters(SelectedManga.getID());
}