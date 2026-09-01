#include "config.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QTextStream>

namespace
{
QString configFilePath()
{
    QString ConfigDir =
        QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

    QDir Dir(ConfigDir);

    if (!Dir.exists())
    {
        Dir.mkpath(".");
    }

    return ConfigDir + "/config.json";
}
}

std::string Config::loadLanguage()
{
    QFile File(configFilePath());

    if (!File.open(QIODevice::ReadOnly))
    {
        return "";
    }

    QByteArray Contents = File.readAll();
    File.close();

    QJsonDocument Document = QJsonDocument::fromJson(Contents);

    return Document.object().value("language").toString().toStdString();
}

void Config::saveLanguage(const std::string& LanguageCode)
{
    QJsonObject Root;

    Root["language"] = QString::fromStdString(LanguageCode);

    QFile File(configFilePath());

    if (File.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        File.write(QJsonDocument(Root).toJson());
        File.close();
    }
}