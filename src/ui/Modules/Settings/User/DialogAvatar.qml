import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import Qt.labs.platform 1.1 as QtLabs

import ui.types 1.0
import "../../../Custom" as Custom
import "../../../Controllers/UserController.js" as JS

Custom.Dialog {
    id: control
    contentHeight: column.implicitHeight + 64
    contentWidth: width * 0.9

    onShowed: {
        errInfo.text = "";
        avatar.setAvatar(userController.ui_currentUser.ui_avatar)
    }

    Connections {
        target: userController

        function onUserAvatarChanged(status) {
//            busyIndicator.running = false;
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
            text: "Change user avatar"
        }

        Item {
            Layout.fillHeight: true
        }

        Custom.Avatar {
            id: avatar
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 150
            Layout.preferredWidth: width
        }

        Custom.String {
            id: info
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
            color: "#CCFFFFFF"
            text: "You can adjust position of image by swipe image and dobule swipe to zoom in/out"
        }

        Item {
            Layout.fillHeight: true
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            spacing: 16

            Custom.Button {
                id: deleteButton
                Layout.fillWidth: true
                Layout.maximumWidth: 100
                Layout.preferredHeight: height
                fontPixel: 12
                text: "Delete"

                onClicked: {
                    avatar.setAvatar("");
                }
            }

            Custom.Button {
                id: chooseButton
                Layout.fillWidth: true
                Layout.maximumWidth: 100
                Layout.preferredHeight: height
                fontPixel: 12
                text: "Choose"

                onClicked: {
                    fileDialog.open();
                }
            }

            Custom.Button {
                id: takeButton
                Layout.fillWidth: true
                Layout.maximumWidth: 100
                Layout.preferredHeight: height
                fontPixel: 12
                text: "Take Photo"

                onClicked: {
                }
            }
        }

        Custom.String {
            id: errInfo
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.margins: 4
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            color: "#D00808"
        }

        Item {
            Layout.fillHeight: true
        }

        //            BusyIndicator {
        //                id: busyIndicator
        //                Layout.alignment: Qt.AlignHCenter
        //                Layout.preferredHeight: 25
        //                Layout.preferredWidth: 25
        //                running: false
        //                visible: running
        //            }

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
//                    busyIndicator.running = true;
                    userController.changeAvatar(avatar.getSource());
                }
            }
        }
    }

//    FileDialog {
//        id: fileDialog
//        title: "Choose image"
//        nameFilters: ["Image files (*.jpg *.jpeg *.png)"]
//        selectExisting: true

//        onAccepted: {
//            let blob = userController.loadAvatar(fileDialog.fileUrl.toString().replace("file:///", ""));
//            avatar.setAvatar(blob);
//        }
//    }

    QtLabs.FileDialog {
        id: fileDialog
        title: "Choose image"
        nameFilters: ["Image files (*.jpg *.jpeg *.png)"]

//        folder: QtLabs.StandardPaths.writableLocation(QtLabs.StandardPaths.DocumentsLocation)
        fileMode: QtLabs.FileDialog.OpenFile
        onAccepted: {
            let blob = userController.loadAvatar(fileDialog.file.toString().replace("file:///", ""));
            avatar.setAvatar(blob);
        }
    }
}

