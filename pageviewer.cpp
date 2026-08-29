#include "pageviewer.h"
#include "provider.h"
#include "mpvviewer.h"

void PageViewer::view(const std::string& ChapterID)
{
    Provider ProviderClient;

    std::vector<std::string> PageURLs =
        ProviderClient.getPageURLs(ChapterID);

    MpvViewer::open(PageURLs);
}