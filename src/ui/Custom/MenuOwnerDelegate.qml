import QtQuick 2.15
import QtQuick.Layouts 1.12

Rectangle {
    id: delegate
    width: ListView.view.width
    anchors.bottomMargin: 24
    height: 110
    radius: 6
    border.width: 1
    border.color: app.styleApp.menuDelegate.borderColor
    color: mouseArea.pressed ? app.styleApp.menuDelegate.backgroundPressedColor : app.styleApp.menuDelegate.backgroundColor

    Behavior on color {
        ColorAnimation {duration: 100}
    }

    signal clicked()

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        spacing: 0

        Avatar {
            id: avatar
            Layout.fillHeight: true
            Layout.topMargin: 10
            Layout.bottomMargin: 10
            Layout.preferredWidth: width
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.leftMargin: 16
            Layout.rightMargin: -20
            spacing: 3

            String {
                id: userName
                Layout.fillWidth: true
                maximumLineCount: 1
                font.pixelSize: 18
                color: "#FFFFFF"
                text: userController.ui_isLogged ? userController.ui_currentUser.ui_name : "Tap to sign in"
            }

            String {
                id: userLogin
                Layout.fillWidth: true
                maximumLineCount: 1
                font.pixelSize: 14
                color: "#66FFFFFF"
                visible: text
                text: userController.ui_isLogged ? userController.ui_currentUser.ui_login : ""
            }
        }

        Icon {
            id: nextArrow
            Layout.fillHeight: true
            Layout.topMargin: 10
            Layout.bottomMargin: 10
            Layout.preferredWidth: height
            Layout.rightMargin: -20
            color: "#FFFFFF"
            source: iconsMap["navigate_next"]
            size: height
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: delegate.clicked()
    }
}
