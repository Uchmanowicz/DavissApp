import QtQuick 2.15
import QtQuick.Layouts 1.12
import "../../Custom" as Custom

Rectangle {
    id: module
    color: "#000000"

    ColumnLayout {
        anchors.top: topBarMenu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Custom.String {
            id: durationTitle
            Layout.alignment: Qt.AlignHCenter
            text: "Your Working Time: " + jobController.ui_timeSummary
            color: "#FFFFFF"

        }
    }


    Custom.TopBarMenu {
        id: topBarMenu
    }

}
