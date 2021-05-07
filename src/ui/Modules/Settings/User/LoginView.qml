import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15
import ui.types 1.0
import "../../../Custom" as Custom
import "../../../Controllers/UserController.js" as JS

Rectangle {
    id: module
    color: "#000000"

    Connections {
        target: userController

        function onSignInResult(status) {
            busyIndicator.running = false;
            errInfo.text = JS.userStatusToText(status);

            if(status === UserController.OK) {
                stackView.replace("qrc:///ui/Modules/Settings/User/LoginViewSummary.qml");
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: app.hideKeyboard()
    }

    ColumnLayout {
        anchors.top: topBarMenu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 32
        spacing: 24

        Custom.String {
            id: loginLabel
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 16
            color: "#FFFFFF"
            text: "Login"
        }

        Custom.StringField {
            id: loginField
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: height
            onAccepted: passwordField.forceActiveFocus()
        }

        Custom.String {
            id: passwordLabel
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 16
            color: "#FFFFFF"
            text: "Password"
        }

        Custom.StringField {
            id: passwordField
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: height
            onAccepted: alwaysLogged.forceActiveFocus()
        }

        Custom.String {
            id: errInfo
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            color: "#D00808"
        }

        CheckBox {
            id: alwaysLogged
            Layout.alignment: Qt.AlignHCenter
            text: "Do not log me out."
        }

        Custom.Button {
            id: loginButton
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 150
            Layout.preferredHeight: height
            text: "Login"

            onClicked: {
                busyIndicator.running = true;
                userController.signIn(loginField.text, passwordField.text, alwaysLogged.checked, false);
            }
        }

        BusyIndicator {
            id: busyIndicator
            Layout.alignment: Qt.AlignHCenter
            running: false
            visible: running
        }

        Item {
            Layout.fillHeight: true
        }
    }

    Custom.TopBarMenu {
        id: topBarMenu
    }
}
