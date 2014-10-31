#include "ytexplorator.h"
#include <QRegExp>
#include <QByteArray>
#include <QUrl>

YtExplorator::YtExplorator(QObject *parent) :
    QObject(parent)
{
}

void YtExplorator::exploreMovieData(QString *ytMovieData)
{
    YtMovie *ytMovie = new YtMovie();

    QRegExp regExp("([^&]+)");
    QRegExp keyAndValueRegExp("^([a-z_]+)=(.*)$");

    int position = 0;
    while (regExp.indexIn(*ytMovieData, position) != -1) {
        QByteArray paramByteArray;
        paramByteArray.append(regExp.cap(1));
        QString param = QUrl::fromPercentEncoding(paramByteArray);

        if (keyAndValueRegExp.indexIn(param) != -1) {
            QByteArray keyByteArray;
            keyByteArray.append(keyAndValueRegExp.cap(1));

            QByteArray valueByteArray;
            valueByteArray.append(keyAndValueRegExp.cap(2));

            this->setYtMovieProperty(ytMovie, QUrl::fromPercentEncoding(keyByteArray), QUrl::fromPercentEncoding(valueByteArray));
        }
        position += regExp.matchedLength() + 1;
    }

    emit ytMovieReady(ytMovie);

    delete ytMovieData;
    ytMovieData = NULL;
}

void YtExplorator::moviesDataReady()
{
    emit ytMoviesReady();
}

void YtExplorator::setYtMovieProperty(YtMovie *ytMovie, QString key, QString value)
{
    if (key == "url") {
        ytMovie->setUrl(value);
    } else if (key == "itag") {
        ytMovie->setItag(value);
    } else if (key == "quality") {
        ytMovie->setQuality(value);
    } else if (key == "type") {
        ytMovie->setType(value);
    } else if (key == "fallback_host") {
        ytMovie->setFallback(value);
    }
}
