#include "mpvviewer.h"

#include <QProcess>
#include <QString>
#include <QStringList>

#include <iostream>

bool MpvViewer::open(
    const std::vector<std::string>& PageURLs
    )
{
    if (PageURLs.empty())
    {
        std::cerr << "No pages to open.\n";
        return false;
    }

    QStringList Arguments;

    Arguments
        << "--http-header-fields=User-Agent: manga-cli (+https://github.com/Procurador1337/manga-cli),Referer: https://mangadex.org/"
        << "--image-display-duration=inf"
        << "--loop-playlist=no"
        << "--force-window=yes"
        << "--title=manga-cli";

    for (const std::string& URL : PageURLs)
    {
        Arguments << QString::fromStdString(URL);
    }

    QProcess Process;

    Process.start("mpv", Arguments);

    if (!Process.waitForStarted())
    {
        std::cerr << "Failed to launch mpv. Is it installed and on your PATH?\n";
        return false;
    }

    Process.waitForFinished(-1);

    return true;
}