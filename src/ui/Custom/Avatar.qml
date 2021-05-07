import QtQuick 2.15
import QtGraphicalEffects 1.12
import QtQuick.Window 2.12

Rectangle {
    id: control
    height: 100
    width: height
    radius: height/2
    color: "transparent"


    property alias xPosition: customImage.x
    property alias yPosition: customImage.y

    function setAvatar(blob) {
        if(blob.length) {
            priv.source = blob;
            priv.convertedSource = "data:image/png;base64," + blob;
        }else {
            priv.source = "";
            priv.convertedSource = "";
        }
    }

    function getSource() {
       return priv.source;
    }

    Component.onCompleted: setAvatar(userController.ui_currentUser.ui_avatar)

    Item {
        id: priv
        property string source: ""
        property string convertedSource: ""
    }

    Connections {
        target: userController

        function onUserChanged() {
            control.setAvatar(userController.ui_currentUser.ui_avatar);
        }
    }

    Image {
        id: customImage
                anchors.fill: parent
//                x: 0 + control.width/2 - width/2
//                y: 0 + control.height/2 - height/2
        //        width: parent.width
        //        height: parent.height
        visible: false
//        fillMode: Image.PreserveAspectCrop
        fillMode: Image.PreserveAspectFit
        source: priv.convertedSource
    }

    Rectangle {
        id: avatarMask
        radius: height/2
        anchors.fill: parent
        smooth: true
        visible: false
    }

    OpacityMask {
        id: mask
                anchors.fill: customImage
        source: customImage
        maskSource: avatarMask
//        width: parent.width
//        height: parent.height
//        x: 0 + control.width/2 - width/2
//        y: 0 + control.height/2 - height/2

//        onXChanged: {
//            if(x > width-5) {
//                x = width-5;
//            }else if (x < -width+5) {
//                x = -width+5
//            }
//        }

    }

    Icon {
        id: defaultImage
        anchors.fill: parent
        size: height
        color: "#FFFFFF"
        source: iconsMap["account_circle"]
        visible: !priv.source.length
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.width: 2
        border.color: "#FFFFFF"
        radius: control.radius
    }

    MouseArea {
        anchors.fill: parent
//        drag.target: mask
    }
}
