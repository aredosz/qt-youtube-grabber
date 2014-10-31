#ifndef XMLCONFIGURATION_H
#define XMLCONFIGURATION_H

#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <iostream>

using namespace std;

class XmlConfiguration
{
public:
    static XmlConfiguration &getInstance(QString filePath = "");
    bool hasError();
    QString getInfoUrl();
    QString getTmpDir();

private:
    QString filePath;
    bool errorOccurred;

    QString infoUrl;
    QString tmpDir;

    XmlConfiguration();
    XmlConfiguration(const XmlConfiguration &);
    XmlConfiguration & operator= (const XmlConfiguration &);
    ~XmlConfiguration();

    void parseXml();
};

#endif // XMLCONFIGURATION_H
