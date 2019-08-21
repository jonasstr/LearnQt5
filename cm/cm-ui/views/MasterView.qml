import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.0

import assets 1.0
import components 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Client Management")

    Connections {
        target: masterController.ui_navigationController
        onGoCreateClientView: contentFrame.replace("qrc:/views/CreateClientView.qml")
        onGoDashboardView: contentFrame.replace("qrc:/views/DashboardView.qml")
        onGoEditClientView: contentFrame.replace("qrc:/views/EditClientView.qml")
        onGoFindClientView: contentFrame.replace("qrc:/views/FindClientView.qml")
    }

    StackView {
        id: contentFrame
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: navigationBar.right
        }
        initialItem: "qrc:/views/SplashView.qml"
    }

    NavigationBar {
       id: navigationBar
    }

    Component.onCompleted: contentFrame.replace("qrc:/views/DashboardView.qml")
}
