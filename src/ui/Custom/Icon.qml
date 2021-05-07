import QtQuick 2.15

Item {
    id: control
    width: icon.implicitWidth
    height: icon.implicitHeight
    visible: source !== ""

    property alias source: icon.text
    property alias size: icon.font.pixelSize
    property alias rotation: icon.rotation
    property alias color: icon.color

    Text {
        id: icon
        anchors.centerIn: parent
        font.pixelSize: 24
        font.family: iconsLoader.name
    }
}
