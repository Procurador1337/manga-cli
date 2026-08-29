#include "pageviewer.h"
#include "provider.h"
#include "networkclient.h"
#include "imagerender.h"
#include "terminalutils.h"

#include <chrono>
#include <iostream>
#include <thread>

void PageViewer::view(const std::string& ChapterID)
{
    Provider ProviderClient;

    std::vector<std::string> PageURLs =
        ProviderClient.getPageURLs(ChapterID);

    if (PageURLs.empty())
    {
        std::cout << "No pages found for this chapter.\n";
        return;
    }

    NetworkClient Client;

    int CurrentPage = 0;

    while (true)
    {
        TerminalSize Size = TerminalUtils::getSize();

        std::cout << "\x1b[2J\x1b[H";

        std::cout
            << "Page "
            << CurrentPage + 1
            << " / "
            << PageURLs.size()
            << "  [n]ext  [p]rev  [q]uit\n\n";

        bool Loaded = false;
        const int MaxAttempts = 3;

        for (int Attempt = 1; Attempt <= MaxAttempts && !Loaded; ++Attempt)
        {
            std::cerr << "Requesting: " << PageURLs[CurrentPage] << '\n';

            try
            {
                std::string ImageData =
                    Client.get(PageURLs[CurrentPage]);

                ImageRenderer::render(
                    ImageData,
                    Size.Columns,
                    Size.Rows - 4
                    );

                Loaded = true;
            }
            catch (const std::exception& Error)
            {
                std::cerr
                    << "Attempt "
                    << Attempt
                    << "/"
                    << MaxAttempts
                    << " failed: "
                    << Error.what()
                    << '\n';

                if (Attempt < MaxAttempts)
                {
                    std::vector<std::string> FreshPageURLs =
                        ProviderClient.getPageURLs(ChapterID);

                    if (!FreshPageURLs.empty() &&
                        FreshPageURLs.size() == PageURLs.size())
                    {
                        PageURLs = FreshPageURLs;
                    }

                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(500)
                        );
                }
                else
                {
                    std::cerr
                        << "Giving up on this page. Press n/p/q.\n";
                }
            }
        }
        int Key = TerminalUtils::readKey();

        if (Key == 'q' || Key == 'Q')
        {
            break;
        }
        else if ((Key == 'n' || Key == 'N' || Key == ' ') &&
                 CurrentPage + 1 < static_cast<int>(PageURLs.size()))
        {
            ++CurrentPage;
        }
        else if ((Key == 'p' || Key == 'P' || Key == 127 || Key == 8) &&
                 CurrentPage > 0)
        {
            --CurrentPage;
        }
    }
            std::cout << "\nWaiting for input...\n";
}