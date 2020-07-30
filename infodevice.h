#ifndef INFODEVICE_H
#define INFODEVICE_H

#include <QNetworkInterface>
#include <QLibraryInfo>
#include <QProcess>
#include <QFile>
#include <unistd.h>
#include <math.h>

class InfoDevice
{
public:
    enum Commands {
        reboot = 0,
        startUpdateApplication,
        stopApplication,
        displayOn,
        displayOff
    };
    QString idDevice();
    QString cpuArchitecture();
    QString hostName();
    QString versionOs();
    QString platformOs();
    QString versionQt();
    QString ipLocal();
    QString idDeviceRasp();
    QString idDeviceModel();
    QString prettyProductName();
    QString cpuUsed();
    QString memoUsed();
    QString uptime();
    QString storeFree();
    QString cpuTemp();
    QString gpuRam();
    QString displayState();
    QString displayModel();
    Q_INVOKABLE void execCommand(Commands);

private:
    QNetworkInterface m_inter;
    QSysInfo m_info;
    QString hexToDecimal(QString);
    int m_prevIdleTime;
    int m_prevTotalTime;
};

#endif // INFODEVICE_H
