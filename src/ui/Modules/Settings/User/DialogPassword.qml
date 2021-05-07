import QtQuick 2.15
import QtQuick.Layouts 1.12
import ui.types 1.0
import "../../../Custom" as Custom
import "../../../Controllers/UserController.js" as JS

Custom.Dialog {
    id: control
    contentHeight: column.implicitHeight + 64
    contentWidth: width * 0.9

    onShowed: {
        errInfo.text = "";
        newPasswordField.clear();
        oldPasswordField.clear();
        confirmPasswordField.clear();
    }

    Connections {
        target: userController

        function onUserPasswordChanged(status) {
            errInfo.text = JS.userStatusToText(status);

            if(status === UserController.OK) {
                control.hide();
            }
        }
    }

    ColumnLayout {
        id: column
        anchors.centerIn: parent
        width: control.contentWidth - 24
        spacing: 20

        Custom.String {
            id: titleLabel
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 20
            font.bold: true
            color: "#FFFFFF"
            text: "Change user password"
        }

        Item {
            Layout.fillHeight: true
        }

        Custom.String {
            id: oldPasswordLabel
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 16
            color: "#FFFFFF"
            text: "Enter old password"
        }

        Custom.StringField {
            id: oldPasswordField
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: height
        }

        Custom.String {
            id: newPasswordLabel
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 16
            color: "#FFFFFF"
            text: "Enter new password"
        }

        Custom.StringField {
            id: newPasswordField
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: height
        }

        Custom.String {
            id: confirmPasswordLabel
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 16
            color: "#FFFFFF"
            text: "Repeat new password"
        }

        Custom.StringField {
            id: confirmPasswordField
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 200
            Layout.preferredHeight: height
        }

        Custom.String {
            id: errInfo
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            color: "#D00808"
        }

        Item {
            Layout.fillHeight: true
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            spacing: 24

            Custom.Button {
                id: cancelButton
                Layout.fillWidth: true
                Layout.maximumWidth: 150
                Layout.preferredHeight: height
                text: "Cancel"

                onClicked: {
                    control.hide();
                }
            }

            Custom.Button {
                id: acceptButton
                Layout.fillWidth: true
                Layout.maximumWidth: 150
                Layout.preferredHeight: height
                isSpecial: true
                text: "Change"

                onClicked: {
                    if(userController.convertPasswordToHash(oldPasswordField.text) !== userController.ui_currentUser.ui_password) {
                        errInfo.text = "Wrong old password";
                        return;
                    }

                    if(oldPasswordField.text === newPasswordField.text) {
                        errInfo.text = "New and old password are the same";
                        return;
                    }

                    if(newPasswordField.text !== confirmPasswordField.text) {
                        errInfo.text = "New passwords are not the same";
                        return;
                    }

                    if(newPasswordField.length < 3) {
                        errInfo.text = "Password must has at least 3 characters";;
                        return;
                    }

                    errInfo.text = "";
                    userController.changePassword(newPasswordField.text);
                }
            }
        }
    }
}
