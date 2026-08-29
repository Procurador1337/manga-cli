#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

#include <string>

class ImageRenderer
{
public:
    static void render(const std::string& ImageData, int MaxColumns, int MaxRows);
};

#endif