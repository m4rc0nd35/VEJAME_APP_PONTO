import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

Page {
    id: mainParent
    header: ToolBar {
        contentHeight: toolButton.implicitHeight
        background: Rectangle {
            color: "#0F2228"
        }
        ToolButton {
            id: toolButton
            Image {
                id: sexoImg
                anchors.centerIn: parent
                source: stackView.depth > 1 ? "img/back.png" : "img/menu.png"
            }
            onClicked: stackView.depth > 1 ? stackView.pop() : drawer.open()
        }
        Label {
            id: idLabel
            text: stackView.currentItem.title
            anchors.centerIn: parent
            color: "#94999E"
        }
        DropShadow {
            anchors.fill: idLabel
            horizontalOffset: 3
            verticalOffset: 3
            radius: 5.0
            samples: 17
            color: "#161616"
            source: idLabel
        }
    }

    Drawer {
        id: drawer
        width: mainParent.width * 0.85
        height: mainParent.height
        background: Rectangle {
            color: "#0F2228"
        }

        Column {
            anchors.fill: parent

            ItemDelegate {
                id: menu
                width: parent.width
                Text {
                    id: userNome
                    anchors.top: menu.top
                    anchors.topMargin: 5
                    anchors.left: imgUser.right
                    anchors.margins: 8
                    color: "#FFFFFF"
                    font.pointSize: 12
                    text: qsTr("NOME PONTO")
                }
                DropShadow {
                    anchors.fill: userNome
                    horizontalOffset: 3
                    verticalOffset: 2
                    radius: 5.0
                    samples: 17
                    color: "#161616"
                    source: userNome
                }
                Text {
                    id: userCpf
                    anchors.top: userNome.bottom
                    anchors.left: imgUser.right
                    anchors.margins: 8
                    color: "#94999E"
                    font.pointSize: 12
                    text: qsTr("CPF ")

                }
                DropShadow {
                    anchors.fill: userCpf
                    horizontalOffset: 3
                    verticalOffset: 2
                    radius: 5.0
                    samples: 17
                    color: "#161616"
                    source: userCpf
                }
                Rectangle {
                    anchors.bottom: menu.bottom
                    height: 3
                    width: parent.width / 1.3
                    color: "#213534"
                }
                onClicked: {
                    drawer.close()
                }
            }

            ItemDelegate {
                id: itemFinan
                width: parent.width
                visible: true
                Image {
                    id:imgFinan
                    anchors.verticalCenter: itemFinan.verticalCenter
                    anchors.left: itemFinan.left
                    anchors.margins: 8
                    source: "img/entrada.png"
                }
                Text {
                    id: txtFinan
                    anchors.verticalCenter: itemFinan.verticalCenter
                    anchors.left: imgFinan.right
                    anchors.margins: 8
                    color: "#FFFFFF"
                    font.pointSize: 12
                    text: qsTr("Presente")
                }
                Rectangle {
                    anchors.bottom: itemFinan.bottom
                    color: "#AED6F1"
                    height: 1
                    width: parent.width
                }
                onClicked: {
                    stackView.push(pagePresente)
                    drawer.close()
                }
            }

            ItemDelegate {
                id: itemPlanos
                width: parent.width
                visible: true
                Image {
                    id:imgPlanos
                    anchors.verticalCenter: itemPlanos.verticalCenter
                    anchors.left: itemPlanos.left
                    anchors.margins: 8
                    source: "img/saida.png"
                }
                Text {
                    id: txtPlanos
                    anchors.verticalCenter: itemPlanos.verticalCenter
                    anchors.left: imgPlanos.right
                    anchors.margins: 8
                    color: "#FFFFFF"
                    font.pointSize: 12
                    text: qsTr("Saida")
                }
                Rectangle {
                    anchors.bottom: itemPlanos.bottom
                    color: "#AED6F1"
                    height: 1
                    width: parent.width
                }
                onClicked: {
                    stackView.push(pageSaida)
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: pageHome
        anchors.fill: parent
    }

    Component {
        id: pageHome
        Agenda{}
    }

    Component {
        id: pagePresente
        Presente{}
    }

    Component {
        id: pageSaida
        Saida{}
    }
}
