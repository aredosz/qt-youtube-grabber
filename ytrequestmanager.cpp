#include "ytrequestmanager.h"

#include <QNetworkRequest>
#include <QByteArray>
#include <QRegExp>
#include <iostream>

#include "xmlconfiguration.h"

using namespace std;

YtRequestManager::YtRequestManager(QObject *parent) :
    QObject(parent)
{
    networkAccessManagerGetYtInfo = new QNetworkAccessManager(this);
    connect(networkAccessManagerGetYtInfo, SIGNAL(finished(QNetworkReply *)), this, SLOT(ytVideoInfoRequestFinished(QNetworkReply *)));
}

void YtRequestManager::getVideoInfo(QString ytVideoId)
{
    QString url;
    QString ytUrlFormat = XmlConfiguration::getInstance().getInfoUrl();
    url.sprintf(ytUrlFormat.toStdString().c_str(), ytVideoId.toStdString().c_str());

    this->requestYtVideoInfo(QUrl(url));
}

void YtRequestManager::ytVideoInfoRequestFinished(QNetworkReply *reply)
{
    if (reply->error()) {
        cout << "Error occurred during YouTube request about video informations." << endl;
        return;
    }

    int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (httpStatusCode == YtRequestManager::HTTP_MOVED_PERMANENTLY && reply->hasRawHeader("Location")) {
        QString newLocation = QString(reply->rawHeader("Location"));
        this->requestYtVideoInfo(QUrl(newLocation));
        return;
    }

    QString videoInfo = QString(reply->readAll());
    QRegExp streamMapRegEx("stream_map=(.[^&]*)&");

    if (streamMapRegEx.indexIn(videoInfo) > -1) {
        QString streamMapMatch = streamMapRegEx.cap(1);
        QByteArray streamMapMatchByteArray;
        streamMapMatchByteArray.append(streamMapMatch);

        QString *decodedMoviesMap = new QString(QUrl::fromPercentEncoding(streamMapMatchByteArray));
        QStringList *chunkedMoviesList = this->getYtMoviesChunks(decodedMoviesMap);

        for (int i=0; i<chunkedMoviesList->size(); i++) {
            emit ytMovieDataReady(new QString(chunkedMoviesList->at(i)));
        }

        delete decodedMoviesMap;
        decodedMoviesMap = NULL;
        delete chunkedMoviesList;
        chunkedMoviesList = NULL;
    }

    emit ytMoviesDataReady();
}

void YtRequestManager::requestYtVideoInfo(QUrl url)
{
    QNetworkRequest ytRequest;
    ytRequest.setUrl(url);
    ytRequest.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:11.0) Gecko Firefox/11.0");
    ytRequest.setRawHeader("Referer", "http://youtube.com/");

    networkAccessManagerGetYtInfo->get(ytRequest);
}

QStringList *YtRequestManager::getYtMoviesChunks(QString *moviesMap)
{
    return new QStringList(moviesMap->split(",", QString::SkipEmptyParts));
}
