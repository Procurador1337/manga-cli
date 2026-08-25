#include "manga.h"

Manga::Manga(const std::string& ID,
             const std::string& Name)
    : ID(ID),
    Name(Name)
{
}

std::string Manga::getID() const
{
    return ID;
}

std::string Manga::getName() const
{
    return Name;
}