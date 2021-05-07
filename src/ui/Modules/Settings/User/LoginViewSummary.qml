import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15
import ui.types 1.0
import "../../../Custom" as Custom

Rectangle {
    id: module
    color: "#000000"

    Connections {
        target: userController

        function onSignInResult(status) {
            busyIndicator.running = false;
            if(status === UserController.OK) {
                errInfo.text = "";
            }else if(status === UserController.WRONG_USER) {
                errInfo.text = "Login or password is incorrect";
            }else if(status === UserController.BLOCKED) {
                errInfo.text = "User has beed blocked. Please contant with admin";
            }else if(status === UserController.NOT_CONNECTION) {
                errInfo.text = "Error with connection to network. Please check your network";
            }else if(status === UserController.NOT_KNOWN) {
                errInfo.text = "Occured not known error";
            }
        }
    }

    ColumnLayout {
        anchors.top: topBarMenu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 32
        spacing: 24

        Custom.String {
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 16
            color: "#FFFFFF"
            text: "Hello <b>" + userController.ui_currentUser.ui_name + "</b> in Daviss community!"
        }

        Custom.String {
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            color: "#FFFFFF"
            text: "Bellow you find some updated infromation about current status of app."
        }

        Item {
            Layout.fillHeight: true
        }
    }

    Custom.TopBarMenu {
        id: topBarMenu
    }
}
