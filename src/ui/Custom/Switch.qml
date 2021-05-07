import QtQuick 2.15

Item {
    id: control
    width: background.width
    height: background.height

    property int value: 0
    property QtObject style: app.styleApp.switchButton

    Rectangle {
        id: background
        width: 70
        height: 20
        radius: 25
        color: !control.enabled ?
                   control.style.backgroundDisabledColor :
                   (control.value ? control.style.backgroundCheckedColor : control.style.backgroundUncheckedColor)
    }


    Rectangle {
        id: pointer
        anchors.verticalCenter: background.verticalCenter
        x: control.value ? background.x + background.width - width : background.x
        height: background.height+10
        width: height
        radius: height/2
        color: !control.enabled ?
                   control.style.buttonDisabledColor :
                   (control.value ? control.style.buttonCheckedColor : control.style.buttonUncheckedColor)

        Behavior on x {
            NumberAnimation {duration: 500}
        }
    }
}
