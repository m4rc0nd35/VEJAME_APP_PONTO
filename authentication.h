#ifndef AUTENTICATION_H
#define AUTENTICATION_H

#include <QObject>
#include <requestapi.h>
#include <infodevice.h>

class Authentication : public RequestApi, private InfoDevice
{
  Q_OBJECT
  Q_PROPERTY(QJsonObject dataUser MEMBER m_dataUser NOTIFY successDataUserChanged)

public:
  explicit Authentication(QObject *parent = nullptr);
  Q_INVOKABLE void login(QString, QString);

private:
  /* Variables */
  QJsonObject m_dataUser;
  QString m_flag;

signals:
  void successDataUserChanged();
  void error(QString message);

private slots:
    void jsonApi(QJsonObject);

};

#endif // AUTENTICATION_H
