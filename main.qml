import QtQuick 2.12
import QtQuick.Controls 2.12
import QtLoadSetup 1.12

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    LoadSetup {
        id: loadSetup
    }

    Component.onCompleted: {
        loadSetup.initApp()
    }

    ScrollView {
        anchors.fill: parent

        ListView {
            width: parent.width
            model: 20
            delegate: ItemDelegate {
                text: "Item " + (index + 1)
                width: parent.width
            }
        }
    }
}
