#ifndef REQUESTAPI_H
#define REQUESTAPI_H
#include <QObject>
#include <QUrl>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QByteArray>
#include <QUrlQuery>
#include <QTcpSocket>
#include <QTimer>

class RequestApi: public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint64 downRecieved MEMBER m_downRecieved NOTIFY downProgressChanged)
    Q_PROPERTY(qint64 downTotal MEMBER m_downTotal NOTIFY downProgressChanged)

public:
    explicit RequestApi(QObject *parent = nullptr);
    void token(QByteArray, QByteArray);
    void setServerApi(QString);
    void post(QString, QJsonObject);
    void get(QString);
    QVariant getSynchro(QString);
    void request(QString, QByteArray, QJsonObject, bool=false);
    void sendFile(QString, QString, QString);
    void download(QString);
    Q_INVOKABLE bool checkServer(QString, quint16);
    Q_INVOKABLE void setHost(QString);
    Q_INVOKABLE void setPort(quint16);
    Q_INVOKABLE void setTokenBearer(QString);

signals:
    void apiJsonObjectFinished(QJsonObject jsonObject);
    void loadingShow(bool show);
    void unauthorizedApiStatusChanged(QJsonObject jsonObject);
    void warningApi(QJsonObject jsonObject);
    void downloadFinished(QByteArray);
    void monitorStateChanged(bool);
    void downProgressChanged();

private slots:
    void readyApi();
    void downloadProgress(qint64 recieved, qint64 total);

private:
    QNetworkAccessManager *m_manager;
    QNetworkRequest m_request;
    QNetworkReply *m_reply;
    QString m_urlAPi;
    quint16 m_port = 80;
    QString m_flagURL;

    qint64 m_downRecieved = 0;
    qint64 m_downTotal = 0;

    bool m_block = false;

};

#endif // REQUESTAPI_H
