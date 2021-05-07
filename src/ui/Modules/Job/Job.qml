import QtQuick 2.15
import Qt.labs.qmlmodels 1.0
import "../../Custom" as Custom

Rectangle {
    id: module
    color: "#000000"

    Component.onCompleted: listModel.prepare()

    enum ListIndex {
        USER_OWNER,
        SPACER_1,
        APPEARANCE_SUBVIEW,
        NETWORK_SUBVIEW
    }

    ListModel {
        id: listModel

     function prepare() {
         listModel.clear();
         listModel.append({type : "owner"});
         listModel.append({type : "spacer"});
         listModel.append({type : "subView", modelName: "Appearance", modelSource: iconsMap["preview"], modelColor: "#FFFFFF"});
         listModel.append({type : "subView", modelName: "Network", modelSource: iconsMap["wifi"], modelColor: "#FFFFFF"});
     }
    }

    DelegateChooser {
        id: delegateChooser
        role: "type"

        DelegateChoice {
            roleValue: "owner"
            Custom.MenuOwnerDelegate {
                onClicked: {
                    switch(model.index) {
                    case Settings.ListIndex.USER_OWNER:
                        if(userController.ui_isLogged) {
                            stackView.push("qrc:///Modules/Settings/UserSettings.qml")
                        }else {
                            stackView.push("qrc:///Modules/Settings/LoginView.qml")
                        }
                        break;
                    }
                }
            }
        }

        DelegateChoice {
            roleValue: "string"
            Custom.MenuStringDelegate {}
        }

        DelegateChoice {
            roleValue: "subView"
            Custom.MenuSubViewDelegate {
                onClicked: {
                    switch(index) {
                    case Settings.ListIndex.APPEARANCE_SUBVIEW:
                        stackView.push("qrc:///Modules/Settings/Appearance/AppearanceMenu.qml");
                        break;

                    case Settings.ListIndex.NETWORK_SUBVIEW:
                        break;
                    }
                }
            }
        }

        DelegateChoice {
            roleValue: "spacer"
            Custom.MenuSpacerDelegate {}
        }
    }

    ListView {
        id: listView
        anchors.top: topBarMenu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 12
        model: listModel
        delegate: delegateChooser
        spacing: 8

    }

    Custom.TopBarMenu {
        id: topBarMenu
    }

}
