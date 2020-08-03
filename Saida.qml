import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

Page {
    id: idPageAgendamentos
    title: qsTr("Saidas")
    background: Rectangle {
        color: "#161616"
    }

    property int id_agenda: 0
    property string nomeAgenda: null

    Component.onCompleted: agendamento.refreshSaida()

    ListView {
        anchors.fill: parent
        model: agendamento.listModelSaida
        spacing: 3
        delegate: Component {
            Rectangle {
                id: idRow
                width: parent.width
                height: 45
                color: "#213534"
                border.color: "#0F2228"
                border.width: .5
                Rectangle {
                    id: idStatus
                    anchors.left: idRow.left
                    anchors.leftMargin: 1
                    anchors.verticalCenter: idRow.verticalCenter
                    width: 43
                    height: 43
                    color: "#94999E"
                    radius: 3
                    Text {
                        anchors.centerIn: idStatus
                        text: (index + 1)
                        color: "#161616"
                    }
                }
                Text {
                    id: nomes
                    anchors.left: idStatus.right
                    anchors.margins: 8
                    anchors.top: idRow.top
                    anchors.topMargin: 3
                    text: qsTr(nome)
                    font.pointSize: 12
                    color: "#94999E"
                }
                Image {
                    id: imgUltimoPgto
                    anchors.left: idStatus.right
                    anchors.margins: 8
                    anchors.bottom: idRow.bottom
                    anchors.bottomMargin: 5
                    source: "img/entrada.png"
                }
                Text {
                    id: txtUltimoPgto
                    anchors.left: imgUltimoPgto.right
                    anchors.margins: 8
                    anchors.bottom: idRow.bottom
                    anchors.bottomMargin: 5
                    text: qsTr(entrada)
                    color: "#94999E"
                    font.pointSize: 10
                }
                Image {
                    id: imgProxVctor
                    anchors.left: txtUltimoPgto.right
                    anchors.margins: 10
                    anchors.bottom: idRow.bottom
                    anchors.bottomMargin: 5
                    source: "img/saida.png"
                }
                Text {
                    anchors.left: imgProxVctor.right
                    anchors.margins: 8
                    anchors.bottom: idRow.bottom
                    anchors.bottomMargin: 5
                    text: qsTr(saida)
                    color: "#94999E"
                    font.pointSize: 10
                }
            }
        }
    }

    Rectangle {
        id: btRefreseh
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        height: 50
        width: 50
        radius: 25
        color: "#73e600"
        layer.enabled: true
        layer.effect: DropShadow {
            horizontalOffset: 0
            verticalOffset: 0
            radius: 10
            samples: 6
        }

        Image {
            id: name
            anchors.centerIn: btRefreseh
            height: 30
            width: 30
            source: "img/refresh.png"
        }

        MouseArea {
            anchors.fill: btRefreseh
            onClicked: agendamento.refreshSaida()
        }
    }
}
