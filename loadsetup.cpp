#include "loadsetup.h"

LoadSetup::LoadSetup(QObject *parent) : RequestApi(parent), InfoDevice()
{
    connect(this, SIGNAL(apiJsonObjectFinished(QJsonObject)), this, SLOT(jsonApi(QJsonObject)));

    setTokenBearer(idDevice());
}
void LoadSetup::initApp()
{
    m_flag = "initApp";
    QJsonObject info;
    info.insert("device", idDevice());
    info.insert("ip_local", ipLocal());
    info.insert("qt_version", versionQt());
    info.insert("prettyProductName", prettyProductName());
    request("/device/_authdevice","GET", info);

    qDebug() << info << endl;
}
void LoadSetup::jsonApi(QJsonObject json)
{ // resposta API

    if(m_flag == "initApp")
    {
        qDebug() << json << endl;
    }
}
