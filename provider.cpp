#include "provider.h"
#include "networkclient.h"

#include <iostream>

std::vector<Manga> Provider::searchManga(
    const std::string& Query
    )
{
    NetworkClient Client;

    try
    {
        std::string Response = Client.get(
            "https://allmanga.to/manga?cty=ALL"
            );

        std::cout << Response << '\n';
    }
    catch (const std::exception& Error)
    {
        std::cerr
            << "Network error: "
            << Error.what()
            << '\n';
    }

    return {};
}

std::vector<Chapter> Provider::getChapters(
    const std::string& MangaID
    )
{
    return {};
}