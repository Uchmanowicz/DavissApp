import QtQuick 2.15

MenuDelegate {
    id: delegate
    text: modelName
    iconSource: modelSource
    iconColor: modelColor
    enableAnimation: false

    Switch {
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.verticalCenter: parent.verticalCenter
        value: modelValue === "true" ? 1 : 0
    }
}
