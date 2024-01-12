#include "debug.h"

#include <QCoreApplication>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLoggingCategory>
#include <QStandardPaths>
#include <iostream>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {

    std::cout << qFormatLogMessage(type, context, msg).toStdString() << std::endl;

    QString sMsg    = qFormatLogMessage(type, context, msg);
    QString logName = "release";

#ifdef QT_DEBUG
    logName = "debug";
#endif

    QString filename = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" +
                       QCoreApplication::applicationName() + "-" + logName + ".log";
    // std::cout << filename.toStdString();
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        QTextStream stream(&file);
        stream << QDateTime::currentDateTime().toString() + " - " + sMsg << "\n";
    }else{
        std::cerr <<"Unable to open file "<< filename.toStdString() << "\n";
    }
    file.close();


}
void initDebug() {
    qInstallMessageHandler(myMessageOutput);
    QLoggingCategory::setFilterRules(loadLoggingRules(":/logging_rules.json"));
    qSetMessagePattern(LOGGING_MESSAGE_PATTERN);
}

QString loadLoggingRules(QString filename) {
    // qDebug() << __FUNCTION__;

    // load the file
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qWarning() << "Logging Rules file missing !!";
    QString rules = file.readAll();
    // qDebug() << rules;
    file.close();

    // parse json
    QJsonParseError jsonError;
    QJsonDocument   doc = QJsonDocument::fromJson(rules.toUtf8(), &jsonError);

    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << QString("Error while parsing rules (%1): %2").arg(filename, jsonError.errorString());
        return "";
    }

    QString ret;

    // load the json into the qmap
    if (doc.isObject()) {
        QJsonObject jsonObj = doc.object();
        foreach (auto topic, jsonObj["rules"].toArray().toVariantList()) {
            qDebug() << "Loading logging rule" << topic.toString();
            ret += topic.toString() + "\n";
        }
    }
    return ret;
}

void logAppInfo() {
    QCoreApplication::setApplicationVersion(APP_VERSION);
    //QCoreApplication::setOrganizationName("greenjuice");
    QCoreApplication::setOrganizationDomain("ynov.greenjuice.fr");

    qInfo() << "Starting" << QCoreApplication::applicationName() + " v" + QCoreApplication::applicationVersion() << "\n"
            << "Build date:" << __DATE__ << __TIME__ << "\n"
            << "organizationDomain:" << QCoreApplication::organizationDomain() << "\n"
            << "organizationName:" << QCoreApplication::organizationName() << "\n"
            << "applicationDirPath:" << QCoreApplication::applicationDirPath() << "\n"
            << "applicationFilePath:" << QCoreApplication::applicationFilePath() << "\n"
            << "APP_VERSION:" << APP_VERSION << "GIT_VERSION:" << GIT_VERSION
            << "\n"
            //     << "UUID:" << QUuid::createUuid() << endl
            << "QSysInfo::machineHostName():" << QSysInfo::machineHostName() << "\n"
            << "QSysInfo::machineUniqueId():" << QSysInfo::machineUniqueId() << "\n"
            << "QSysInfo::prettyProductName():" << QSysInfo::prettyProductName() << QSysInfo::currentCpuArchitecture() << "\n"
            << "QStandardPaths::writableLocation():" << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) << "\n"
            << "\n";
}
