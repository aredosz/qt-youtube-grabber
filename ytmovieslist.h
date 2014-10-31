#ifndef YTMOVIESLIST_H
#define YTMOVIESLIST_H

#include <QObject>
#include <QList>
#include "ytmovie.h"

class YtMoviesList : public QObject
{
    Q_OBJECT
public:
    explicit YtMoviesList(QObject *parent = 0);

signals:
    void downloadYtVideo(QString *url);
    void emptyListError();

public slots:
    void addYtMovie(YtMovie *ytMovie);
    void sortMovies();

private:
    QList<YtMovie*> movies;

    static bool lessThan(const YtMovie *a, const YtMovie *b);
    void clearList();
};

#endif // YTMOVIESLIST_H
