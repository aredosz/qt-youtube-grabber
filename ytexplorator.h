#ifndef YTEXPLORATOR_H
#define YTEXPLORATOR_H

#include <QObject>
#include <QString>
#include "ytmovie.h"

class YtExplorator : public QObject
{
    Q_OBJECT
public:
    explicit YtExplorator(QObject *parent = 0);

signals:
    void ytMovieReady(YtMovie *ytMovie);
    void ytMoviesReady();

public slots:
    void exploreMovieData(QString *ytMovieData);
    void moviesDataReady();

private:
    void setYtMovieProperty(YtMovie *ytMovie, QString key, QString value);

};

#endif // YTEXPLORATOR_H
