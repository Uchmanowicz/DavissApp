import QtQuick 2.15

Rectangle {
    id: control
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    height: 60
    color: app.styleApp.topBar

    Icon {
        id: backwardButton
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 5
        anchors.bottomMargin: 5
        anchors.rightMargin: 12
        size: height
        source: iconsMap["arrow_back"]

        MouseArea {
            anchors.fill: parent
            onClicked: stackView.pop(null);
        }
    }
}
