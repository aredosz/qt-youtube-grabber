#ifndef YTMOVIE_H
#define YTMOVIE_H

#include <QObject>
#include <QString>

class YtMovie : public QObject
{
    Q_OBJECT
public:
    explicit YtMovie(QObject *parent = 0);

    QString getType() const;
    void setType(const QString &value);

    QString getItag() const;
    void setItag(const QString &value);

    QString getUrl() const;
    void setUrl(const QString &value);

    QString getQuality() const;
    void setQuality(const QString &value);

    QString getFallback() const;
    void setFallback(const QString &value);

signals:

public slots:

private:
    QString type;
    QString itag;
    QString url;
    QString quality;
    QString fallback;

};

#endif // YTMOVIE_H
