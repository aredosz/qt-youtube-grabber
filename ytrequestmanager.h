#ifndef YTREQUESTMANAGER_H
#define YTREQUESTMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QString>
#include <QStringList>
#include <QNetworkReply>

class YtRequestManager : public QObject
{
    Q_OBJECT
public:
    explicit YtRequestManager(QObject *parent = 0);

    void getVideoInfo(QString ytVideoId);

signals:
    void ytMovieDataReady(QString *ytMovieData);
    void ytMoviesDataReady();


public slots:
    void ytVideoInfoRequestFinished(QNetworkReply *reply);

private:
    static const int HTTP_MOVED_PERMANENTLY = 301;

    QNetworkAccessManager *networkAccessManagerGetYtInfo;

    void requestYtVideoInfo(QUrl url);
    QStringList *getYtMoviesChunks(QString *moviesMap);
};

#endif // YTREQUESTMANAGER_H
