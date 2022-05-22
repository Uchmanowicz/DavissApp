import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import "../../../Custom" as Custom

Rectangle {
    id: module
    color: "#000000"

    Component.onCompleted: listModel.prepare()

    property bool readyToUpdate: true

    Connections {
        target: userController

        function onUserChanged() {
//            if(module.readyToUpdate) {
            listModel.prepare();
//                stackView.replace("qrc:///ui/Modules/Settings/User/UserSettings.qml", StackView.Immediate);
//            }
        }
    }

    enum ListIndex {
        SIGN_OUT_ACTION,
        NAME_STRING,
        ROLE_STRING,
        SPACER_1,
        ALWAYS_SIGNED_IN_ACTION,
        CHANGE_NAME_ACTION,
        CHANGE_PASSWORD_ACTION,
        CHANGE_AVATAR_ACTION
    }

    ListModel {
        id: listModel

        function prepare() {
            listModel.clear();
            listModel.append({type : "action", modelName: "SING OUT", modelSource: iconsMap["logout"], modelColor: "#FFFFFF"});
            listModel.append({type : "string", modelName: "Name", modelValue: userController.ui_currentUser.ui_name, modelSource: "", modelColor: "#56606D"});
            listModel.append({type : "string", modelName: "Role", modelValue: userController.ui_currentUser.ui_userRoleDisplay, modelSource: "", modelColor: "#56606D"});
            listModel.append({type : "spacer"});
            listModel.append({type : "switch", modelName: "Always signed in", modelValue: String(userController.ui_currentUser.ui_isAlwaysLogged), modelSource: iconsMap["edit"], modelColor: "#FFFFFF"});
            listModel.append({type : "action", modelName: "Change name", modelSource: iconsMap["edit"], modelColor: "#FFFFFF"});
            listModel.append({type : "action", modelName: "Change password", modelSource: iconsMap["edit"], modelColor: "#FFFFFF"});
            listModel.append({type : "action", modelName: "Change avatar", modelSource: iconsMap["edit"], modelColor: "#FFFFFF"});
        }
    }

    DelegateChooser {
        id: delegateChooser
        role: "type"

        DelegateChoice {
            roleValue: "action"
            Custom.MenuActionDelegate {
                onClicked: {
                    switch(index) {
                    case UserSettings.ListIndex.SIGN_OUT_ACTION:
                        stackView.pop();
                        userController.signOut();
                        break;

                    case UserSettings.ListIndex.CHANGE_PASSWORD_ACTION:
                        dialogPassword.show();
                        break;

                    case UserSettings.ListIndex.CHANGE_NAME_ACTION:
                        dialogName.show();
                        break;

                    case UserSettings.ListIndex.CHANGE_AVATAR_ACTION:
                        dialogAvatar.show();
                        break;
                    }
                }
            }
        }

        DelegateChoice {
            roleValue: "switch"
            Custom.MenuSwitchDelegate {
                onClicked: {
                    switch(index) {
                    case UserSettings.ListIndex.ALWAYS_SIGNED_IN_ACTION:
                        userController.changeAlwaysSigned(!userController.ui_currentUser.ui_isAlwaysLogged);
                        break;
                    }
                }
            }
        }

        DelegateChoice {
            roleValue: "string"
            Custom.MenuStringDelegate {
                onClicked: {
                    switch(index) {

                    }
                }
            }
        }

        DelegateChoice {
            roleValue: "subView"
            Custom.MenuSubViewDelegate {
                onClicked: {
                    switch(index) {

                    }
                }
            }
        }

        DelegateChoice {
            roleValue: "spacer"
            Custom.MenuSpacerDelegate {}
        }
    }

    Custom.Avatar {
        id: avatar
        anchors.top: topBarMenu.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 12
        height: 100
    }

    ListView {
        id: listView
        anchors.top: avatar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 12
        clip: true
        model: listModel
        delegate: delegateChooser
        spacing: 8

    }

    Custom.TopBarMenu {
        id: topBarMenu
    }

    DialogName {
        id: dialogName
    }

    DialogPassword {
        id: dialogPassword
    }

    DialogAvatar {
        id: dialogAvatar
    }
}
