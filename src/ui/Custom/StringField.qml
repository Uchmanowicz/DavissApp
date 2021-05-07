import QtQuick 2.15
import QtQuick.Controls 2.12

TextField {
    id: control
    objectName: "StringInput"

    property alias button: buttonLoader.sourceComponent
    property QtObject style: app.styleApp.stringField

    height: 60
    verticalAlignment: TextField.AlignVCenter
    selectByMouse: true

//    font.family: poppinsMedium.name
//    font.weight: Font.Medium
    font.pixelSize: 16

    leftPadding: 16
    rightPadding: buttonLoader.visible ? buttonLoader.width : 12
    topPadding: 0
    bottomPadding: 0

    color: control.style.textColor
    placeholderTextColor: control.style.placeholderTextColor
    selectionColor: control.style.selectionColor
    selectedTextColor: control.style.selectedTextColor

    cursorDelegate: Rectangle {
        visible: blinkingTimer.cursorVisible
        color: control.style.cursorColor
        width: control.cursorRectangle.width
    }

    background: Rectangle {
        color: "transparent"
    }

    onActiveFocusChanged: if(control.activeFocus) {
                              blinkingTimer.start()
                          }else {
                              blinkingTimer.stop()
                              blinkingTimer.cursorVisible = false
                          }

    Timer {
        id: blinkingTimer
        repeat: control.activeFocus
        interval: 500
        onTriggered: cursorVisible = !cursorVisible

        property bool cursorVisible: true
    }

    Rectangle {
        anchors.fill: parent
        color: control.style.background
        border.width: 1
        border.color: control.activeFocus ? control.style.focusedBorderColor : control.style.borderColor
        radius: 4
        z: -1

        Loader {
            id: buttonLoader
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            width: height
            visible: sourceComponent !== null
        }
    }
}
