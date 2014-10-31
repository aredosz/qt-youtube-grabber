#include "ytdownloader.h"
#include <QNetworkRequest>
#include <QUrl>
#include <iostream>
#include <QFile>
#include <QDir>
#include <QTime>
#include <QCoreApplication>

#include "xmlconfiguration.h"

using namespace std;

YtDownloader::YtDownloader(QObject *parent) :
    QObject(parent)
{
    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

void YtDownloader::downloadYtVideo(QString *url)
{
    QNetworkRequest ytRequest;
    ytRequest.setUrl(QUrl(*url));
    ytRequest.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:11.0) Gecko Firefox/11.0");
    ytRequest.setRawHeader("Referer", "http://youtube.com/");

    cout << "start downloading" << endl;

    networkAccessManager->get(ytRequest);

    delete url;
}

void YtDownloader::replyFinished(QNetworkReply *reply)
{
    if (reply->error()) {
        cout << "Error during downloading youtube movie.";
    } else {
        this->createTmpDir();

        QString tmpDir = XmlConfiguration::getInstance().getTmpDir();
        QString filePath = tmpDir + this->generateFileName();

        QFile *movie = new QFile(filePath);
        if (movie->open(QFile::Append)) {
            movie->write(reply->readAll());
            movie->flush();
            movie->close();
        }
        delete movie;
    }
    reply->deleteLater();

    cout << "stop downloading" << endl;

    QCoreApplication::exit();
}

void YtDownloader::createTmpDir()
{
    QString tmpDir = XmlConfiguration::getInstance().getTmpDir();
    QDir directory("./");
    if (!directory.exists(tmpDir)) {
        directory.mkpath(tmpDir);
    }
}

QString YtDownloader::generateFileName()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int numericValue = (qrand() % 1000) + 1;
    return QString("ytmovie_%1").arg(numericValue);
}
