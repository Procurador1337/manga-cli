#include "cli.h"
#include "config.h"

#include <algorithm>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    for (int Index = 1; Index < argc; ++Index)
    {
        std::string Argument = argv[Index];

        if (Argument == "--setlang")
        {
            if (Index + 1 >= argc)
            {
                std::cerr << "Usage: manga-cli --setlang <language-code>\n";
                return 1;
            }

            std::string LanguageCode = argv[Index + 1];

            std::transform(
                LanguageCode.begin(),
                LanguageCode.end(),
                LanguageCode.begin(),
                ::tolower
                );

            Config::saveLanguage(LanguageCode);

            std::cout
                << "Language set to \""
                << LanguageCode
                << "\".\n";

            return 0;
        }
    }

    CLI App;

    return App.run();
}