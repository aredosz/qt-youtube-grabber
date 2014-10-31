#include "xmlconfiguration.h"


XmlConfiguration::XmlConfiguration()
{
    this->errorOccurred = false;
}

XmlConfiguration::~XmlConfiguration()
{
}

XmlConfiguration &XmlConfiguration::getInstance(QString filePath)
{
    static XmlConfiguration instance;

    if (instance.filePath.length() == 0) {
        instance.filePath = filePath;
        instance.parseXml();
    }

    return instance;
}

void XmlConfiguration::parseXml()
{
    QFile *configurationXmlFile = new QFile(this->filePath);
    if (!configurationXmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "I can't open xml file..." << endl;
        this->errorOccurred = true;
        return;
    }

    QXmlStreamReader stream(configurationXmlFile);
    while (!stream.atEnd() && !stream.hasError()) {
        QXmlStreamReader::TokenType token = stream.readNext();
        if (token == QXmlStreamReader::StartDocument) {
            continue;
        }

        if (token == QXmlStreamReader::StartElement) {
            if (stream.name() == "info_url") {
                stream.readNext();
                this->infoUrl = stream.text().toString();
            } else if (stream.name() == "tmp_dir") {
                stream.readNext();
                this->tmpDir = stream.text().toString();
            }
        }
    }
}

bool XmlConfiguration::hasError() {
    return this->errorOccurred;
}

QString XmlConfiguration::getInfoUrl() {
    return this->infoUrl;
}

QString XmlConfiguration::getTmpDir()
{
    return this->tmpDir;
}
