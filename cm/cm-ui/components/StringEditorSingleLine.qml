import QtQuick 2.9
import CM 1.0
import assets 1.0

Item {

    property StringDecorator stringDecorator
    height: width > textLabel.width + textValue.width ? Style.heightDataControls : Style.heightDataControls * 2

    Flow {
        anchors.fill: parent

        Rectangle {
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colorBackground

            Text {
                id: textLabel
                anchors {
                    fill: parent
                    margins: Style.heightDataControls / 4
                }
                text: stringDecorator.ui_label
                color: Style.colorDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }
        }

        Rectangle {
            id: background
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colorDataControlsBackground
            border {
                width: 1
                color: Style.colorDataControlsFont
            }

            TextInput {
                id: textValue
                anchors {
                    fill: parent
                    margins: Style.heightDataControls / 4
                }
                text: stringDecorator.ui_value
                color: Style.colorDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }
        }

        Binding {
            target: stringDecorator
            property: "ui_value"
            value: textValue.text
        }
    }
}
