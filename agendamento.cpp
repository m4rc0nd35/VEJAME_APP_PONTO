#include "agendamento.h"

Agendamento::Agendamento(QObject *parent) : RequestApi(parent)
{
    m_aganda = new AbstractListModel({"id","nome","atraso","entrada","saida","state"});
    m_presente = new AbstractListModel({""});
    m_saida = new AbstractListModel({""});

    connect(this, SIGNAL(apiJsonObjectFinished(QJsonObject)), this, SLOT(jsonApi(QJsonObject)));
}
void Agendamento::refreshAll()
{
    m_flag = "refreshAll";
    get("/app/");
}
void Agendamento::refreshAgenda()
{
    m_flag = "refreshAgenda";
    get("/app/_lista_agenda");
}
void Agendamento::refreshPresente()
{
    m_flag = "refreshPresente";
    get("/app/_lista_presente");
}
void Agendamento::refreshSaida()
{
    m_flag = "refreshSaida";
    get("/app/_lista_saida");
}
void Agendamento::agendaState(int idAgenda, int state)
{
    m_flag = "agendaState";
    QJsonObject data;
    data.insert("idAgenda", idAgenda);
    data.insert("state", state);
    request("/app/_agenda_state", "PUT", data);
}
void Agendamento::jsonApi(QJsonObject json)
{
    if(m_flag == "refreshAgenda")
    {
        m_aganda->reload(json["content"].toObject()["lista"].toArray());
        m_totalPresente = json["content"].toObject()["presente"].toInt();
    }
    else if(m_flag == "refreshPresente")
        m_aganda->reload(json["content"].toArray());

    else if(m_flag == "refreshSaida")
        m_aganda->reload(json["content"].toArray());

    else if(m_flag == "agendaState")
    {
        QJsonObject content = json["content"].toObject();
        qDebug() << content << endl;
        m_aganda->reload(content["listaAgenda"].toArray());
        m_presente->reload(content["listaPresente"].toArray());
        m_saida->reload(content["listaSaida"].toArray());
        m_totalPresente = content["presente"].toInt();
    }

    emit successChanged();
}
