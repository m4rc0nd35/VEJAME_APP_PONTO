import QtQuick 2.12
import QtQuick.Controls 2.12
import QtAuthentication 1.12
import QtAgendamento 1.12

ApplicationWindow {
    id: window
    visible: true
    title: qsTr("Veja-Me")

    property bool popupHold: false
    property bool toastVisible: false
    property string msgs: ""

    Authentication {
        id: authentication
        onUnauthorizedApiStatusChanged: {
            msgs = "Autenticação inválida!"
            toastVisible = true
        }
        onLoadingShow: loadingApi.visible = show
        onSuccessDataUserChanged: {
            agendamento.setTokenBearer(dataUser.access_token)
            mainStackView.push(pageMain)
        }
    }

    Agendamento {
        id: agendamento
        onUnauthorizedApiStatusChanged: toastVisible = true
        onLoadingShow: loadingApi.visible = show
    }

    Component.onCompleted: {
        authentication.setHost(hostApiArg)
        authentication.setPort(portApi)

        agendamento.setHost(hostApiArg)
        agendamento.setPort(portApi)
    }

    StackView {
        id: mainStackView
        anchors.fill: parent
        initialItem: pageAuthentication
    }

    Component {
        id: pageAuthentication
        AuthenticationPage{}
    }

    Component {
        id: pageMain
        MainAppPage{}
    }

    /* Toast */
    Popup {
        id: toast
        x: (parent.width / 2 - (toast.width / 2))
        y: (parent.height / 1.2)
        width: 250
        height: 45
        visible: toastVisible
        background: Rectangle {
            id: bgToast
            radius: 5
            color: "#000000"
            opacity: .3
        }

        Text {
            anchors.centerIn: parent
            text: qsTr(msgs)
            color: "#D5DBDB"
        }

        Timer {
            interval: 3000
            running: toastVisible
            onTriggered:{
                toastVisible = false;
            }
        }
    }

    /* Loading */
    Popup {
        id: loadingApi
        width: parent.width
        height: parent.height
        z: 10
        visible: false
        modal: true
        closePolicy: loadingApi.CloseOnEscape | loadingApi.CloseOnPressOutside
        background: Rectangle {
            radius: 10
            color: "#000"
            opacity: .1
        }

        AnimatedImage {
            source: "img/loading.gif"
            anchors.centerIn: parent
        }
    }
}
