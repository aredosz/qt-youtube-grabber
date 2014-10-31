#ifndef YTDOWNLOADER_H
#define YTDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

class YtDownloader : public QObject
{
    Q_OBJECT
public:
    explicit YtDownloader(QObject *parent = 0);

signals:

public slots:
    void downloadYtVideo(QString *url);
    void replyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkAccessManager;

    void createTmpDir();
    QString generateFileName();

};

#endif // YTDOWNLOADER_H
