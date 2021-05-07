import QtQuick 2.15

MenuDelegate {
    id: delegate
    text: modelName
    iconSource: modelSource
    iconColor: modelColor

    Icon {
        id: nextArrow
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 12
        anchors.bottomMargin: 12
        anchors.rightMargin: 12
        color: "#FFFFFF"
        source: iconsMap["double_arrow"]
        size: height
    }
}
