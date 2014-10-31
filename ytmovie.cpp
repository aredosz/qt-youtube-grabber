#include "ytmovie.h"

YtMovie::YtMovie(QObject *parent) :
    QObject(parent)
{
}
QString YtMovie::getType() const
{
    return type;
}

void YtMovie::setType(const QString &value)
{
    type = value;
}
QString YtMovie::getItag() const
{
    return itag;
}

void YtMovie::setItag(const QString &value)
{
    itag = value;
}
QString YtMovie::getUrl() const
{
    return url;
}

void YtMovie::setUrl(const QString &value)
{
    url = value;
}

QString YtMovie::getQuality() const
{
    return quality;
}

void YtMovie::setQuality(const QString &value)
{
    quality = value;
}
QString YtMovie::getFallback() const
{
    return fallback;
}

void YtMovie::setFallback(const QString &value)
{
    fallback = value;
}
