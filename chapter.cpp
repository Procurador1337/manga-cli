#include "chapter.h"

Chapter::Chapter(const std::string& ID,
                 const std::string& Name)
    : ID(ID),
    Name(Name)
{
}

std::string Chapter::getID() const
{
    return ID;
}

std::string Chapter::getName() const
{
    return Name;
}