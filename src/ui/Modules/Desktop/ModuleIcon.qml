import QtQuick 2.15
import QtGraphicalEffects 1.0

import "../../Custom" as Custom

Rectangle {
    id: control
    color: "transparent"
    width: 80
    height: 80
    visible: source !== ""
    scale: 1

    property string source: ""
    property string name: ""

    signal clicked()
    signal pressed()
    signal released()

    Behavior on scale {
        NumberAnimation {duration: 200}
    }

    DropShadow {
        id: shadow
        anchors.fill: background
        source: background
        horizontalOffset: 0
        verticalOffset: 8
        radius: 10
        samples: 17
        color: "#40000000"
    }

    Rectangle {
        id: background
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: 52
        height: 52
        color: "#CC5C637E"
        radius: 10
        border.width: 2
        border.color: "#99000000"
    }

    Image {
        id: icon
        anchors.fill: parent
        source: control.source
    }

    Custom.String {
        id: name
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 56
        color: "#FFFFFF"
        text: control.name
        font.pixelSize: 14
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            clickingTimer.start();
            control.scale = 1.3;
        }

        onReleased: {
            if(clickingTimer.running) {
                control.clicked()
                clickingTimer.stop();
                control.scale = 1;
            }
            control.scale = 1;
        }

        Timer {
            id: clickingTimer
            running: false
            interval: 300

            onTriggered: control.pressed();
        }
    }
}
