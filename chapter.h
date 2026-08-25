#ifndef CHAPTER_H
#define CHAPTER_H

#include <string>

class Chapter
{
public:
    Chapter(const std::string& ID,
            const std::string& Name);

    std::string getID() const;
    std::string getName() const;

private:
    std::string ID;
    std::string Name;
};

#endif