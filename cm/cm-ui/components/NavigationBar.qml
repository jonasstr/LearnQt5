import QtQuick 2.9
import assets 1.0

Item {
    property bool isCollapsed: true
    clip: true

    anchors {
        top: parent.top
        bottom: parent.bottom
        left: parent.left
    }
    width: isCollapsed ? Style.widthNavigationBarCollapsed : Style.widthNavigationBarExpanded

    Rectangle {
        anchors.fill: parent
        color: Style.colorNavigationBarBackground

        Column {
            width: parent.width;

            NavigationButton {
                iconCharacter: "\uf0c9"
                description: ""
                hoverColor: "#e74c3c"
                onNavigationButtonClicked: isCollapsed = !isCollapsed;
            }
            NavigationButton {
                iconCharacter: "\uf015"
                description: "Dashboard"
                hoverColor: "#e67e22"
                onNavigationButtonClicked: masterController.ui_navigationController.goDashboardView()            }
            NavigationButton {
                iconCharacter: "\uf234"
                description: "New Client"
                hoverColor: "#2ecc71"
                onNavigationButtonClicked: masterController.ui_navigationController.goCreateClientView()
            }
            NavigationButton {
                iconCharacter: "\uf002"
                description: "Find Client"
                hoverColor: "#3498db"
                onNavigationButtonClicked: masterController.ui_navigationController.goFindClientView();
            }
        }
    }
}
