#ifndef MANGA_H
#define MANGA_H

#include <string>

class Manga
{
public:
    Manga(const std::string& Name);

    std::string getName() const;

private:
    std::string Name;
};

#endif