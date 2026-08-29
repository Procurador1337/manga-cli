#ifndef MPVVIEWER_H
#define MPVVIEWER_H

#include <string>
#include <vector>

class MpvViewer
{
public:
    static bool open(const std::vector<std::string>& PageURLs);
};

#endif