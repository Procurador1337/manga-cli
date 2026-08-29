#include "networkclient.h"

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QUrl>

#include <stdexcept>


std::string NetworkClient::get(const std::string& URL)
{
    QUrl RequestURL(QString::fromStdString(URL));

    if (!RequestURL.isValid() ||
        RequestURL.scheme() != "https")
    {
        throw std::runtime_error(
            "Only valid HTTPS URLs are allowed."
            );
    }

    QNetworkAccessManager Manager;

    QNetworkRequest Request(RequestURL);

    Request.setTransferTimeout(10000);

    QNetworkReply* Reply = Manager.get(Request);


//The api requires this to work properly
    Request.setHeader(QNetworkRequest::UserAgentHeader, "manga-cli (+https://github.com/Procurador1337/manga-cli)");

    QEventLoop Loop;

    QObject::connect(
        Reply,
        &QNetworkReply::finished,
        &Loop,
        &QEventLoop::quit
        );

    Loop.exec();

    if (Reply->error() != QNetworkReply::NoError)
    {
        std::string Error =
            Reply->errorString().toStdString();

        Reply->deleteLater();

        throw std::runtime_error(Error);
    }

    std::string Response =
        Reply->readAll().toStdString();

    Reply->deleteLater();

    return Response;
}