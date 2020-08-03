#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include <QObject>
#include <requestapi.h>
#include <abstractlistmodel.h>

class Agendamento : public RequestApi
{
  Q_OBJECT
  Q_PROPERTY(AbstractListModel *listModelAgenda MEMBER m_aganda NOTIFY successChanged)
  Q_PROPERTY(AbstractListModel *listModelPresente MEMBER m_presente NOTIFY successChanged)
  Q_PROPERTY(AbstractListModel *listModelSaida MEMBER m_saida NOTIFY successChanged)
  Q_PROPERTY(int totalPresente MEMBER m_totalPresente NOTIFY successChanged)

public:
  explicit Agendamento(QObject *parent = nullptr);
  Q_INVOKABLE void refreshAgenda();
  Q_INVOKABLE void refreshPresente();
  Q_INVOKABLE void refreshSaida();
  Q_INVOKABLE void refreshAll();
  Q_INVOKABLE void agendaState(int, int);

signals:
  void successChanged();

private slots:
  void jsonApi(QJsonObject);

private:
  QString m_flag;
  AbstractListModel *m_aganda;
  AbstractListModel *m_presente;
  AbstractListModel *m_saida;
  int m_totalPresente = 0;

};

#endif // AGENDAMENTO_H
