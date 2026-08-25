#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <string>

class NetworkClient
{
public:
    std::string get(const std::string& URL);
};

#endif