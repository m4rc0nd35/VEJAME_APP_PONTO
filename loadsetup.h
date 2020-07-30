#ifndef LOADSETUP_H
#define LOADSETUP_H

#include <infodevice.h>
#include <requestapi.h>
#include <QObject>
#include <QTimer>
#include <abstractlistmodel.h>

class LoadSetup : public RequestApi, private InfoDevice
{
    Q_OBJECT
    Q_PROPERTY(QString idDevice MEMBER m_idDevice NOTIFY successUpdateChanged)
    Q_PROPERTY(bool displayShow MEMBER m_displayShow NOTIFY displayShowChanged)
    Q_PROPERTY(int limite MEMBER m_limite NOTIFY successUpdateChanged)

public:
    explicit LoadSetup(QObject *parent = nullptr);
    Q_INVOKABLE void initApp();

signals:
    void successUpdateChanged(QJsonObject content);
    void displayShowChanged();

private slots:
    void jsonApi(QJsonObject);

private:
    QString m_idDevice;
    QString m_flag;
    QString m_startHour;
    QString m_stopHour;
    QString m_daysOfWeek;
    QString m_expire;
    bool m_displayShow;
    int m_limite = 0;
    QString m_nomePonto;

};

#endif // LOADSETUP_H
