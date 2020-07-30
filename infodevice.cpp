#include "infodevice.h"

QString InfoDevice::idDevice()
{
    return m_info.machineUniqueId().toUpper().replace("-","");
}
QString InfoDevice::idDeviceRasp()
{
    QString serial = "0000000000";
        QProcess myProcess;
        myProcess.start("bash", QStringList() << "-c" << "cat /proc/cpuinfo | grep Serial | cut -d ' ' -f 2");
        if (!myProcess.waitForFinished())
          qDebug() << "Make output:" << myProcess.readAll();
        else
          serial = myProcess.readAll().replace("\n","");

    return hexToDecimal(serial);
}
QString InfoDevice::idDeviceModel()
{ // case raspberry, get serial processor
    QString model = "NO_MODEL";
    if(m_info.currentCpuArchitecture() == "arm")
    {
        QProcess myProcess;
        myProcess.start("bash", QStringList() << "-c" << "cat /proc/device-tree/model");
//        myProcess.start("bash", QStringList() << "-c" << "cat /proc/cpuinfo | grep Model | cut -d ':' -f 2");
        if (myProcess.waitForFinished())
            model = myProcess.readAll().replace("\n","");
    }
    return model;
}
QString InfoDevice::cpuUsed()
{ // case linux, get percent usage CPU
    QString cpuUsage = "0";
    QFile file("/proc/stat");
    file.open(QFile::ReadOnly);
    const QList<QByteArray> times = file.readLine().simplified().split(' ').mid(1);
    const int idleTime = times.at(3).toInt();
    int totalTime = 0;
    foreach (const QByteArray &time, times) {
        totalTime += time.toInt();
    }
    cpuUsage = QString::number((1 - (1.0*idleTime-m_prevIdleTime) / (totalTime-m_prevTotalTime)) * 100.0, 'f', 2);
    m_prevIdleTime = idleTime;
    m_prevTotalTime = totalTime;
    return cpuUsage;
}
QString InfoDevice::memoUsed()
{ // case linux, get percent usage memory
    QProcess myProcess;
    QString model = "0";
    myProcess.start("bash", QStringList() << "-c" << "free -m | grep Mem | awk '{print (($3 + $5) / $2) * 100}'");
    if (myProcess.waitForFinished())
        model = myProcess.readAll().replace("\n","");

    return model;
}
QString InfoDevice::uptime()
{
    QProcess myProcess;
    QString time = "0";
    myProcess.start("bash", QStringList() << "-c" << "uptime | egrep -o 'up*.*[0-9]+:[0-9]+|up*.*[0-9]+\\smin'");
    if (myProcess.waitForFinished())
        time = myProcess.readAll().replace("\n","");

    return time;
}
QString InfoDevice::storeFree()
{
    QProcess myProcess;
    QString sd = "0";
    myProcess.start("bash", QStringList() << "-c" << "df -h | grep /dev/root | awk '{gsub(\"G\",\"\");print $3\":\"$2}'");
    if (myProcess.waitForFinished())
      sd = myProcess.readAll().replace("\n","");

    return sd;
}
QString InfoDevice::cpuTemp()
{
    QProcess myProcess;
    QString temp = "0";
    myProcess.start("bash", QStringList() << "-c" << "vcgencmd measure_temp | egrep -o '[0-9]*\\.[0-9]*'");
    if (myProcess.waitForFinished())
      temp = myProcess.readAll().replace("\n","");

    return temp;
}
QString InfoDevice::gpuRam()
{
    QProcess myProcess;
    QString gpu = "0";
    myProcess.start("bash", QStringList() << "-c" << "vcgencmd get_mem gpu | egrep -o '[0-9]*'");
    if (myProcess.waitForFinished())
      gpu = myProcess.readAll().replace("\n","");

    return gpu;
}
QString InfoDevice::displayState()
{
    QProcess myProcess;
    QString state = "0";
    myProcess.start("bash", QStringList() << "-c" << "vcgencmd display_power | egrep -o '[0-9]*'");
    if (myProcess.waitForFinished())
      state = myProcess.readAll().replace("\n","");

    return state;
}
QString InfoDevice::displayModel()
{
    QProcess myProcess;
    QString model = "not";
    myProcess.start("bash", QStringList() << "-c" << "tvservice -name | awk '{gsub(\"device_name=\",\"\",$1);print $1}'");
    if (myProcess.waitForFinished())
      model = myProcess.readAll().replace("\n","");

    return model;
}
void InfoDevice::execCommand(Commands cmm)
{
    QProcess myProcess;
    QStringList line_commmand;
    line_commmand.append("-c");
    switch (cmm) {
      case Commands::reboot:
        line_commmand.append("reboot");
        break;
      case Commands::startUpdateApplication:
        line_commmand.append("systemctl stop application.service");
        line_commmand.append("&&");
        line_commmand.append("systemctl start ota.service");
        break;
      case Commands::stopApplication:
        line_commmand.append("systemctl stop vejame.service");
        break;
      case Commands::displayOn:
        line_commmand.append("vcgencmd display_power 1");
        break;
      case Commands::displayOff:
        line_commmand.append("vcgencmd display_power 0");
        break;
    }
    myProcess.start("bash" , line_commmand);
    if (myProcess.waitForFinished())
        qDebug() << "output:" << myProcess.readAll();
}
QString InfoDevice::cpuArchitecture()
{
    return m_info.currentCpuArchitecture();
}
QString InfoDevice::hostName()
{
    return m_info.machineHostName();
}
QString InfoDevice::versionOs()
{
    return m_info.prettyProductName();
}
QString InfoDevice::platformOs()
{
    return m_info.productType();
}
QString InfoDevice::versionQt()
{
    return QLibraryInfo::version().toString();
}
QString InfoDevice::prettyProductName()
{
    return m_info.prettyProductName();
}
QString InfoDevice::ipLocal()
{
    qDebug() << "IPS" << m_inter.hardwareAddress()<< endl;
    if(m_info.currentCpuArchitecture() == "arm")
        return m_inter.allAddresses()[2].toString();
    else if(m_info.currentCpuArchitecture() == "x86_64")
        return m_inter.allAddresses()[3].toString();
    else if(m_info.currentCpuArchitecture() == "arm64")
      return m_inter.allAddresses()[7].toString();
    else
        return m_inter.allAddresses()[1].toString();

}
QString InfoDevice::hexToDecimal(QString hexVal)
{
    int pot = hexVal.count();
    int bit = 16;
    double dec_val = 0;

    for (int i = 0; pot > i; i++)
    {
        QString hexString(hexVal.at(i));
        bool ok;
        int index = hexString.toInt(&ok, bit);
        double pows = pow(bit, ((pot - i) - 1));
        double pote = index * pows;
        dec_val += pote;
    }
    return QString::number(dec_val, 'd', 15).split(".")[0];
}
