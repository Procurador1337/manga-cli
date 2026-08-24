#include "manga.h"

Manga::Manga(const std::string& Name)
    : Name(Name)
{
}

std::string Manga::getName() const
{
    return Name;
}