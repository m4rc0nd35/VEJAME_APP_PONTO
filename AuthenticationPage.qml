import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


Page {
    id: autParent
    background: Rectangle {
        color: "#1a1a1a"
    }

    Image {
        id: img_logo
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        width: 220
        height: 200
        source: "img/Prancheta.png"
    }

    Column {
        spacing: 30
        anchors.centerIn: parent

        TextField {
            id: campoLogin
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 20
            font.bold: true
            placeholderText: "Digite seu usuário"
            focus: false
            text: "marcondes"
            background: Rectangle {
                implicitWidth: 300
                implicitHeight: 50
                radius: 5
                color: "#161616"
                border.color: '#213534'
                border.width: .5
            }
        }

        TextField {
            id: campoSenha
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 20
            font.bold: true
            placeholderText: "Digite sua senha"
            echoMode: TextInput.Password
            focus: true
            text: "321654"
            background: Rectangle {
                implicitWidth: 300
                implicitHeight: 50
                radius: 5
                color: "#161616"
                border.color: '#213534'
                border.width: .5
            }
        }

        Button {
            id: btLogar
            anchors.horizontalCenter: parent.horizontalCenter
            height: 40
            width: 300
            font.pointSize: 15
            text: "AUTENTICAR"
            enabled: popupHold ? false : true

            contentItem: Text {
                text: btLogar.text
                font: btLogar.font
                opacity: enabled ? 1.0 : 0.3
                color: "#94999E"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                implicitWidth: btLogar.width
                implicitHeight: btLogar.height
                radius: 5
                color: "#0F2228"
                border.color: '#213534'
                border.width: .5
            }

            onClicked: {
                authentication.login(campoLogin.text, campoSenha.text);
            }
        }

        Keys.onEnterPressed: {
            authentication.login(campoLogin.text, campoSenha.text);
        }
    }

    footer : Rectangle {
        id: idFooter
        Text {
            anchors.bottom: idFooter.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: idFooter.horizontalCenter
            text: "[ Powered by VejaMe.com.br ]"
            font.pointSize: 10
            color: "#94999E"
        }
    }
}
