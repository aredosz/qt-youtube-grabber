#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>
#include "ytrequestmanager.h"
#include "ytexplorator.h"
#include "ytmovieslist.h"
#include "ytdownloader.h"

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationController(QObject *parent = 0);
    void run();

signals:

public slots:
    void ytAccessDenied();

private:
    YtRequestManager *ytRequestManager;
    YtExplorator *ytExplorator;
    YtMoviesList *ytMoviesList;
    YtDownloader *ytDownloader;

};

#endif // APPLICATIONCONTROLLER_H
