#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <authentication.h>
#include <agendamento.h>

int main(int argc, char *argv[])
{
  QString hostApi = "mobile.vejame.com.br";
  QString portApi = "5100";

  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  qmlRegisterType<Authentication>("QtAuthentication", 1, 12, "Authentication");
  qmlRegisterType<Agendamento>("QtAgendamento", 1, 12, "Agendamento");

  engine.rootContext()->setContextProperty("hostApiArg", hostApi);
  engine.rootContext()->setContextProperty("portApi", portApi);

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
