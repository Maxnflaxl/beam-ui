import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.0
import "."

Rectangle {
    id: panel
    radius: 10
    color: Style.background_second

    clip: true

    property string value
    property alias color: panel.color
    property var onOpenExternal: null

    signal copyValueText()

    SFText {
        id: title
        font {
            pixelSize: 18
            styleName: "Bold"; weight: Font.Bold
        }

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.leftMargin: 30
        
        color: Style.content_main
        //% "Available"
        text: qsTrId("available-panel-available")
    }
    Item {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 33
        anchors.rightMargin: 30
        width: whereToBuy.width + 10 + whereToBuyIcon.width
        height: 15

        SFText {
            id: whereToBuy
            font.pixelSize: 14
            anchors.right: whereToBuyIcon.left
            anchors.top: parent.top
            anchors.rightMargin: 10
            
            color: Style.active
            opacity: 0.5
            //% "Where to buy BEAM?"
            text: qsTrId("available-panel-where-to-buy")
        }
        SvgImage {
            id: whereToBuyIcon
            anchors.top: parent.top
            anchors.right: parent.right
            source: "qrc:/assets/icon-external-link.svg"
        }
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if (onOpenExternal && typeof onOpenExternal === 'function') {
                    onOpenExternal();
                }
            }
            hoverEnabled: true
        }
    }

    RowLayout
    {
        id: amount
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: title.left
        spacing: 18

        SvgImage {
            Layout.topMargin:   23
            source:             "qrc:/assets/beam-circle.svg"
            sourceSize:         Qt.size(34, 34)
        }

        BeamAmount {
            Layout.topMargin:   20
            Layout.rightMargin: 25
            amount:             value
            color:              Style.content_secondary
            fontSize:           38
            iconSize:           30
            iconTop:            5
            spacing:            8
        }
    }
}
