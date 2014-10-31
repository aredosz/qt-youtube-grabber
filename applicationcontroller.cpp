#include "applicationcontroller.h"
#include <iostream>
#include <QCoreApplication>
#include <QStringList>

using namespace std;

ApplicationController::ApplicationController(QObject *parent) :
    QObject(parent)
{
    ytExplorator = new YtExplorator(this);
    ytMoviesList = new YtMoviesList(this);
    ytRequestManager = new YtRequestManager(this);
    ytDownloader = new YtDownloader(this);
}

void ApplicationController::run()
{
    connect(ytMoviesList, SIGNAL(emptyListError()), this, SLOT(ytAccessDenied()));

    connect(ytRequestManager, SIGNAL(ytMovieDataReady(QString*)), ytExplorator, SLOT(exploreMovieData(QString*)));
    connect(ytRequestManager, SIGNAL(ytMoviesDataReady()), ytExplorator, SLOT(moviesDataReady()));

    connect(ytExplorator, SIGNAL(ytMovieReady(YtMovie*)), ytMoviesList, SLOT(addYtMovie(YtMovie*)));
    connect(ytExplorator, SIGNAL(ytMoviesReady()), ytMoviesList, SLOT(sortMovies()));

    connect(ytMoviesList, SIGNAL(downloadYtVideo(QString*)), ytDownloader, SLOT(downloadYtVideo(QString*)));

    QStringList arguments = QCoreApplication::arguments();

    if (arguments.size() > 1) {
        ytRequestManager->getVideoInfo(arguments.last());
    }
}

void ApplicationController::ytAccessDenied()
{
    cout << "You can't read data for given videoId.";
}
