import QtQuick 2.15
import QtQuick.Controls 2.15
import Beam.Wallet 1.0
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import "../utils.js" as Utils
import "../controls"

Item {
    default property alias content: contentLayout.data
    property alias buttons: buttonsRow.data
    property alias background: backgroundRect

    Rectangle {
        id: backgroundRect
        color: Style.background_main
        anchors.fill: parent
    }

    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.fill: parent
        anchors.topMargin: 50

        ColumnLayout {
            id: contentLayout
            Layout.fillWidth:   true
            Layout.alignment:   Qt.AlignHCenter
        }
        Item {
            Layout.fillHeight: true
            Layout.fillWidth:  true
            Layout.minimumHeight: 50
        }

        Row {
            id: buttonsRow
            Layout.alignment: Qt.AlignHCenter
            spacing: 30
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth:  true
            Layout.minimumHeight: 67
            Layout.maximumHeight: 143
        }
    }
    VersionFooter {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 40
        anchors.topMargin: 40
    }
}