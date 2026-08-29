#ifndef MANGA_H
#define MANGA_H

#include <string>

class Manga
{
public:
    Manga(const std::string& ID,
          const std::string& Name);

    std::string getID() const;
    std::string getName() const;

    void setChapterCount(int Count);
    int getChapterCount() const;

private:
    std::string ID;
    std::string Name;
    int ChapterCount = -1;
};

#endif