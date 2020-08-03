#include "authentication.h"

Authentication::Authentication(QObject *parent) : RequestApi(parent), InfoDevice()
{
    connect(this, SIGNAL(apiJsonObjectFinished(QJsonObject)), this, SLOT(jsonApi(QJsonObject)));
}
void Authentication::login(QString username, QString passwd)
{
    m_flag = "login";
    QJsonObject dataUser;
    dataUser.insert("username", username);
    dataUser.insert("password", passwd);
    dataUser.insert("qt_version", passwd);
    dataUser.insert("prettyProductName", passwd);
    dataUser.insert("ip_local", passwd);
    request("/app/_auth_mobile","GET", dataUser);
    qDebug() << dataUser << endl;
}
void Authentication::jsonApi(QJsonObject json)
{
    qDebug() << json << endl;
    if(json["result"].toBool())
    {
        if(m_flag == "login")
        {
            m_dataUser = json["content"].toObject();
            emit successDataUserChanged();
        }
    }
    else
    {
        QString message = json["message"].toString();
        emit error(message);
    }
}
