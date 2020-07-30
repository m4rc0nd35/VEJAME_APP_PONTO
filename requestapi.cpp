#include "requestapi.h"

RequestApi::RequestApi(QObject *parent) : QObject(parent)
{
    /* Instâcia */
    m_manager = new QNetworkAccessManager();
}
bool RequestApi::checkServer(QString h, quint16 p)
{
    QTcpSocket socket;
    bool state = false;
    socket.connectToHost(h, p);
    if(socket.waitForConnected(2000))
        state = true;
    else
        state = false;
    emit monitorStateChanged(state);
    return state;
}
void RequestApi::request(QString url, QByteArray method, QJsonObject payload, bool inputType)
{
    if(!m_block)
    {
        m_flagURL = url;
        m_block = true;
        emit loadingShow(true);
        m_request.setUrl(QUrl(QString("http://%1:%2%3").arg(m_urlAPi).arg(m_port).arg(url))); // Url do WebServer
        if(inputType)
        {
            m_request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain; charset=UTF-8");

            QUrlQuery query;
            foreach(const QString &r, payload.keys())
                query.addQueryItem(r,payload.value(r).toString());
            m_reply = m_manager->sendCustomRequest(m_request, method, query.toString(QUrl::FullyEncoded).toUtf8());
        }
        else
        {
            m_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            m_reply = m_manager->sendCustomRequest(m_request, method, QJsonDocument(payload).toJson());
        }
        connect(m_reply, SIGNAL(finished()), this, SLOT(readyApi())); // Signal finished
        connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
    }
}
void RequestApi::get(QString url)
{
    if(!m_block)
    {
        m_flagURL = url;
        m_block = true;
        emit loadingShow(true);
        m_request.setUrl(QUrl(QString("http://%1:%2%3").arg(m_urlAPi).arg(m_port).arg(url))); // Url do WebServer
        m_reply = m_manager->get(m_request); // request GET
        connect(m_reply, SIGNAL(finished()), this, SLOT(readyApi())); // Signal finished
        connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
    }
}
QVariant RequestApi::getSynchro(QString url)
{
    if(!m_block)
    {
        m_flagURL = url;
        m_block = true;
        emit loadingShow(true);
        m_request.setUrl(QUrl(QString("http://%1:%2%3").arg(m_urlAPi).arg(m_port).arg(url))); // Url do WebServer
        m_reply = m_manager->get(m_request); // request GET
        m_reply->waitForReadyRead(10000);
    }
    m_block = false;
    return  m_reply->readAll();
}
void RequestApi::post(QString url, QJsonObject payload)
{
    if(!m_block)
    {
        m_flagURL = url;
        m_block = true;
        emit loadingShow(true);
        m_request.setUrl(QUrl(QString("http://%1:%2%3").arg(m_urlAPi).arg(m_port).arg(url))); // Url do WebServer
        m_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        m_reply = m_manager->post(m_request, QJsonDocument(payload).toJson()); // request POST
        connect(m_reply, SIGNAL(finished()), this, SLOT(readyApi())); // Signal finished
        connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
    }
}
void RequestApi::sendFile(QString url, QString input, QString payload)
{
    if(!m_block)
    {
        m_flagURL = url;
        m_block = true;
        emit loadingShow(true);
        m_request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
        m_request.setUrl(QUrl(QString("http://%1:%2%3").arg(m_urlAPi).arg(m_port).arg(url))); // Url do WebServer
        QUrlQuery query;
        query.addQueryItem(input, payload);
        m_reply = m_manager->post(m_request, query.toString(QUrl::FullyEncoded).toUtf8()); // request POST
        connect(m_reply, SIGNAL(finished()), this, SLOT(readyApi())); // Signal finished
        connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
    }
}
void RequestApi::download(QString url)
{
  if(!m_block)
    {
        m_flagURL = url;
        m_block = true;
        emit loadingShow(true);
        m_request.setUrl(QUrl(QString(url))); // Url do WebServer
        m_reply = m_manager->get(m_request); // request POST
        connect(m_reply, SIGNAL(finished()), this, SLOT(readyApi())); // Signal finished
        connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
    }
}
void RequestApi::token(QByteArray tokenKey, QByteArray tokenValue)
{
    /* Token de autenticação */
    m_request.setRawHeader(tokenKey, tokenValue);
}
void RequestApi::setServerApi(QString url)
{
    /* set server address */
    m_urlAPi = url;
}
void RequestApi::setHost(QString h)
{
    m_urlAPi = h;
}
void RequestApi::setPort(quint16 p)
{
    m_port = p;
}
void RequestApi::setTokenBearer(QString t)
{
    m_request.setRawHeader(QByteArray("Authorization"), QByteArray(QString("Bearer %1").arg(t).toUtf8()));
}
void RequestApi::downloadProgress(qint64 recieved, qint64 total)
{
    m_downRecieved = recieved;
    m_downTotal = total;
    emit downProgressChanged();
}
void RequestApi::readyApi()
{
    QByteArray byteArray = m_reply->readAll();
    QJsonDocument jsonApi = QJsonDocument::fromJson(byteArray);
    QJsonObject jsonResponse;
    switch (m_reply->error()) {
    case QNetworkReply::NoError:
        emit apiJsonObjectFinished(jsonApi.object());
        emit downloadFinished(byteArray);
        break;
    case QNetworkReply::AuthenticationRequiredError:
        emit unauthorizedApiStatusChanged(jsonResponse);
        jsonResponse.insert("message", "Por favor, autentique-se!");
        break;
    case QNetworkReply::UnknownNetworkError:
        emit warningApi(jsonResponse);
        break;
    case QNetworkReply::TimeoutError:
        jsonResponse.insert("message", "Timeout conexão com servidor!");
        emit warningApi(jsonResponse);
        break;
    case QNetworkReply::RemoteHostClosedError:
        jsonResponse.insert("message", "Não foi possivel estabelecer conexão com servidor!");
        emit warningApi(jsonResponse);
        break;
    case QNetworkReply::InternalServerError:
        jsonResponse.insert("message", "Erro interno com servidor!");
        emit warningApi(jsonResponse);
        break;
    case QNetworkReply::ConnectionRefusedError:
        jsonResponse.insert("message", "Conexão recusada com servidor!");
        emit warningApi(jsonResponse);
        break;
    case QNetworkReply::ProtocolInvalidOperationError:
        jsonResponse.insert("message", "Protocolo de conexão invalido!");
        emit warningApi(jsonResponse);
        break;
    default:
        emit warningApi(jsonResponse);
        break;
    }
    emit loadingShow(false);
    m_reply->deleteLater();
    m_block = false;
}
