#include <QCoreApplication>

#include "xmlconfiguration.h"
#include "applicationcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    XmlConfiguration::getInstance("config.xml");
    if (XmlConfiguration::getInstance().hasError()) {
        return 1;
    }

    ApplicationController applicationController;
    applicationController.run();

    return a.exec();
}
