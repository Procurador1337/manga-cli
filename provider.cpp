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

            Results.emplace_back(ID, extractTitle(TitleObject));
        }
    }
    catch (const std::exception& Error)
    {
        std::cerr << "Network error: " << Error.what() << '\n';
    }

    return Results;
}

std::vector<Chapter> Provider::getChapters(
    const std::string& MangaID
    )
{
    NetworkClient Client;

    std::vector<Chapter> Results;

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