#include "provider.h"
#include "networkclient.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QUrl>
#include <QUrlQuery>

#include <iostream>

namespace
{
std::string extractTitle(const QJsonObject& TitleObject)
{
    if (TitleObject.contains("en"))
    {
        return TitleObject.value("en").toString().toStdString();
    }

    if (!TitleObject.isEmpty())
    {
        return TitleObject.begin().value().toString().toStdString();
    }

    return "Unknown Title";
}
}

std::vector<Manga> Provider::searchManga(
    const std::string& Query
    )
{
    NetworkClient Client;

    std::vector<Manga> Results;

    QUrl RequestURL("https://api.mangadex.org/manga");

    QUrlQuery Parameters;
    Parameters.addQueryItem("title", QString::fromStdString(Query));
    Parameters.addQueryItem("limit", "20");
    Parameters.addQueryItem("order[relevance]", "desc");

    RequestURL.setQuery(Parameters);

    try
    {
        std::string Response =
            Client.get(RequestURL.toString().toStdString());

        QJsonDocument Document =
            QJsonDocument::fromJson(QByteArray::fromStdString(Response));

        QJsonArray DataArray = Document.object().value("data").toArray();

        for (const QJsonValue& Entry : DataArray)
        {
            QJsonObject MangaObject = Entry.toObject();

            std::string ID =
                MangaObject.value("id").toString().toStdString();

            QJsonObject TitleObject =
                MangaObject.value("attributes")
                    .toObject()
                    .value("title")
                    .toObject();

            Manga NewManga(ID, extractTitle(TitleObject));
            NewManga.setChapterCount(getChapterCount(ID));
            Results.push_back(NewManga);
        }
    }
    catch (const std::exception& Error)
    {
        std::cerr << "Network error: " << Error.what() << '\n';
    }

    return Results;
}

std::vector<Chapter> Provider::getChapters(
    const std::string& MangaID,
    int Offset,
    int& OutTotal
    )
{
    NetworkClient Client;

    std::vector<Chapter> Results;

    OutTotal = 0;

    QUrl RequestURL(
        QString::fromStdString(
            "https://api.mangadex.org/manga/" + MangaID + "/feed"
            )
        );

    QUrlQuery Parameters;
    Parameters.addQueryItem("translatedLanguage[]", "en");
    Parameters.addQueryItem("order[volume]", "asc");
    Parameters.addQueryItem("order[chapter]", "asc");
    Parameters.addQueryItem("limit", "100");
    Parameters.addQueryItem("offset", QString::number(Offset));

    RequestURL.setQuery(Parameters);

    try
    {
        std::string Response =
            Client.get(RequestURL.toString().toStdString());

        QJsonDocument Document =
            QJsonDocument::fromJson(QByteArray::fromStdString(Response));

        QJsonObject Root = Document.object();

        OutTotal = Root.value("total").toInt();

        QJsonArray DataArray = Root.value("data").toArray();

        for (const QJsonValue& Entry : DataArray)
        {
            QJsonObject ChapterObject = Entry.toObject();

            std::string ID =
                ChapterObject.value("id").toString().toStdString();

            QJsonObject Attributes =
                ChapterObject.value("attributes").toObject();

            QString ChapterNumber = Attributes.value("chapter").toString();
            QString Title = Attributes.value("title").toString();

            QString DisplayName =
                ChapterNumber.isEmpty()
                    ? QString("Oneshot")
                    : "Chapter " + ChapterNumber;

            if (!Title.isEmpty())
            {
                DisplayName += ": " + Title;
            }

            Results.emplace_back(ID, DisplayName.toStdString());
        }
    }
    catch (const std::exception& Error)
    {
        std::cerr << "Network error: " << Error.what() << '\n';
    }

    return Results;
}

std::vector<std::string> Provider::getPageURLs(
    const std::string& ChapterID
    )
{
    NetworkClient Client;

    std::vector<std::string> PageURLs;

    QUrl RequestURL(
        QString::fromStdString(
            "https://api.mangadex.org/at-home/server/" + ChapterID
            )
        );

    try
    {
        std::string Response =
            Client.get(RequestURL.toString().toStdString());

        QJsonDocument Document =
            QJsonDocument::fromJson(QByteArray::fromStdString(Response));

        QJsonObject Root = Document.object();

        std::string BaseURL =
            Root.value("baseUrl").toString().toStdString();

        QJsonObject ChapterObject =
            Root.value("chapter").toObject();

        std::string Hash =
            ChapterObject.value("hash").toString().toStdString();

        QJsonArray DataArray =
            ChapterObject.value("data").toArray();

        for (const QJsonValue& Entry : DataArray)
        {
            std::string Filename = Entry.toString().toStdString();

            PageURLs.push_back(
                BaseURL + "/data/" + Hash + "/" + Filename
                );
        }
    }
    catch (const std::exception& Error)
    {
        std::cerr << "Network error: " << Error.what() << '\n';
    }

    return PageURLs;
}

int Provider::getChapterCount(
    const std::string& MangaID
    )
{
    NetworkClient Client;

    QUrl RequestURL(
        QString::fromStdString(
            "https://api.mangadex.org/manga/" + MangaID + "/aggregate"
            )
        );

    QUrlQuery Parameters;
    Parameters.addQueryItem("translatedLanguage[]", "en");

    RequestURL.setQuery(Parameters);

    int Count = 0;

    try
    {
        std::string Response =
            Client.get(RequestURL.toString().toStdString());

        QJsonDocument Document =
            QJsonDocument::fromJson(QByteArray::fromStdString(Response));

        QJsonObject VolumesObject =
            Document.object().value("volumes").toObject();

        const QStringList VolumeKeys = VolumesObject.keys();

        for (const QString& VolumeKey : VolumeKeys)
        {
            QJsonObject VolumeObject =
                VolumesObject.value(VolumeKey).toObject();

            QJsonObject ChaptersObject =
                VolumeObject.value("chapters").toObject();

            Count += ChaptersObject.size();
        }
    }
    catch (const std::exception& Error)
    {
        std::cerr << "Network error: " << Error.what() << '\n';
    }

    return Count;
}