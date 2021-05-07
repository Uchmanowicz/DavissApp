import QtQuick 2.15
import Qt.labs.qmlmodels 1.0
import "../../Custom" as Custom

Rectangle {
    id: module
    color: "#000000"

    Component.onCompleted: listModel.prepare()

    onVisibleChanged: {
    }

    Connections {
        target: modulesController

        function onModulesChanged() {
            listModel.prepare();
        }
    }

    Connections {
        target: userController

        function onUserChanged() {
            listModel.prepare();
        }
    }

    enum ListIndex {
        USER_OWNER,
        SPACER_1,
        ABOUT_SUBVIEW,
        APPEARANCE_SUBVIEW,
        NETWORK_SUBVIEW,
        SPACER_2
    }

    ListModel {
        id: listModel

        function prepare() {
            listModel.clear();
            listModel.append({type : "owner"});
            listModel.append({type : "spacer"});
            listModel.append({type : "subView", modelName: "About", modelSource: iconsMap["info"], modelColor: "#FFFFFF"});
            listModel.append({type : "subView", modelName: "Appearance", modelSource: iconsMap["preview"], modelColor: "#FFFFFF"});
            listModel.append({type : "subView", modelName: "Network", modelSource: iconsMap["wifi"], modelColor: "#FFFFFF"});
            listModel.append({type : "spacer"});

            let modules = modulesController.ui_modules;
            for(let i in modules) {
                let module = modules[i];
                if(module.ui_isEnabled) {
                    listModel.append({type : "subView", modelName: module.ui_name, modelSource: module.ui_icon, modelColor: "#FFFFFF"});
                }
            }
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
                            stackView.push("qrc:///ui/Modules/Settings/User/UserSettings.qml")
                        }else {
                            stackView.push("qrc:///ui/Modules/Settings/User/LoginView.qml")
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
                        stackView.push("qrc:///ui/Modules/Settings/Appearance/AppearanceMenu.qml");
                        break;

                    case Settings.ListIndex.NETWORK_SUBVIEW:
                        stackView.push("qrc:///ui/Modules/Settings/Network/NetworkMenu.qml");
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
