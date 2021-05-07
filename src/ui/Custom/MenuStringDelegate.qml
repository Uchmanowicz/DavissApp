import QtQuick 2.15

MenuDelegate {
    id: delegate
    text: modelName
    iconSource: modelSource
    iconColor: modelColor
    enableAnimation: false

    String {
        id: subText
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.left: parent.left
        anchors.leftMargin: parent.width/2
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 16
        text: modelValue
        color: "#FFFFFF"
    }
}
