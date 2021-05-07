import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0

import ui.types 1.0
import "../../../Custom" as Custom

Rectangle {
    id: module
    color: "#000000"

    Component.onCompleted: listModel.prepare()

    Connections {
        target: appController

        function onAppChanged() {
            listModel.prepare();
        }
    }

    enum ListIndex {
        SYNC_SWITCH
    }

    ListModel {
        id: listModel

        function prepare() {
            listModel.clear();
            listModel.append({type : "switch", modelName: "Synchronizing", modelValue: String(appController.ui_app.ui_synchronizing), modelSource: iconsMap["sync"], modelColor: "#FFFFFF"});
        }
    }

    DelegateChooser {
        id: delegateChooser
        role: "type"

        DelegateChoice {
            roleValue: "switch"
            Custom.MenuSwitchDelegate {
                onClicked: {
                    switch(index) {
                    case NetworkMenu.ListIndex.SYNC_SWITCH:
                        appController.changeSynchronizing(!appController.ui_app.ui_synchronizing)
                        break;
                    }
                }
            }
        }
    }

    ListView {
        id: listView
        anchors.top: topBarMenu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 12
        anchors.topMargin: 24
        model: listModel
        delegate: delegateChooser
        spacing: 8

    }

    Custom.TopBarMenu {
        id: topBarMenu
    }
}
