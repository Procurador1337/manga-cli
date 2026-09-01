#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config
{
public:
    static std::string loadLanguage();
    static void saveLanguage(const std::string& LanguageCode);
};

#endif