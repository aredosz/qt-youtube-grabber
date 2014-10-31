#include "ytmovieslist.h"

#include <QMap>

#include <QDebug>

YtMoviesList::YtMoviesList(QObject *parent) :
    QObject(parent)
{
}

void YtMoviesList::addYtMovie(YtMovie *ytMovie)
{
    movies.append(ytMovie);
}

void YtMoviesList::sortMovies()
{
    if (!movies.isEmpty()) {
        qSort(movies.begin(), movies.end(), YtMoviesList::lessThan);

        QString *url = new QString(movies.first()->getUrl());
        this->clearList();

        emit downloadYtVideo(url);
    } else {
        emit emptyListError();
    }
}

bool YtMoviesList::lessThan(const YtMovie *a, const YtMovie *b)
{
    QMap<QString, int> ytItagMap;
    ytItagMap["37"] = 1;
    ytItagMap["22"] = 2;
    ytItagMap["18"] = 3;
    ytItagMap["35"] = 4;
    ytItagMap["34"] = 5;
    ytItagMap["6"] = 6;
    ytItagMap["5"] = 7;
    ytItagMap["43"] = 8;
    ytItagMap["36"] = 9;
    ytItagMap["17"] = 10;
    ytItagMap["13"] = 11;

    int priorityA = ytItagMap.contains(a->getItag()) ? ytItagMap[a->getItag()] : 100;
    int priorityB = ytItagMap.contains(b->getItag()) ? ytItagMap[b->getItag()] : 100;

    return priorityA < priorityB;
}

void YtMoviesList::clearList()
{
    while (!movies.isEmpty()) {
        delete movies.takeFirst();
    }
}
