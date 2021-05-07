import QtQuick 2.15
import QtQuick.Layouts 1.12

import "../../Custom" as Custom

Rectangle {
    id: module
    color: "#000000"

    //    Image {
    //        id: wallpaper
    //        anchors.fill: parent
    //        source: "qrc:///ui/Images/Wallpaper/Fire"
    //    }


    Image {
        id: topImage
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 12
        fillMode: Image.PreserveAspectFit
        source: "qrc:///ui/Images/Logo/BarLogo"
    }

//    Rectangle {
//        id: topBar
//        anchors.top: parent.top
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.margins: 12
//        height: topImage.height
//        radius: 6
//        color: "#000000"

//        Image {
//            id: topImage
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.horizontalCenter: parent.horizontalCenter
//            source: "qrc:///ui/Images/Logo/BarLogo"
//        }
//    }

    Rectangle {
        id: menu
        anchors.top: topImage.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: settingsButton.top
        anchors.margins: 12
        color: app.styleApp.menuDelegate.backgroundColor
        border.width: 2
        border.color: app.styleApp.menuDelegate.borderColor
        radius: 6

        GridLayout {
            id: grid
//            anchors.fill: parent
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 24

            columns: 3
            rowSpacing: 24
//            columnSpacing: 24

            Repeater{
                model: modulesController ? modulesController.ui_modules : 0

                delegate:  ModuleIcon {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredHeight: height
                    Layout.preferredWidth: width
                    source: modelData.ui_moduleIcon
                    name: modelData.ui_name

                    onClicked: {
                        stackView.push("qrc:///ui/Modules/" + modelData.ui_id + "/" + "MainView.qml");
                    }

                    onPressed: {
                    }

                    onReleased: {
                    }
                }
            }

        }

    }





    Custom.Icon {
        id: settingsButton
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 12
        source: iconsMap["settings"]
        size: 48
        color: "#FFFFFF"

        MouseArea {
            anchors.fill: parent
            onClicked: stackView.push("qrc:///ui/Modules/Settings/Settings.qml")
        }
    }
}
