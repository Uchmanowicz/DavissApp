import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0

import ui.types 1.0
import "../../../Custom" as Custom

Rectangle {
    id: module
    color: "#000000"

    Component.onCompleted: listModel.prepare()

    enum ListIndex {
        BLUE_ACTION,
        RED_ACTION
    }

    ListModel {
        id: listModel

        function prepare() {
            listModel.clear();
            listModel.append({type : "action", modelName: "Blue", modelSource: "", modelColor: "#5C637E"});
            listModel.append({type : "action", modelName: "Red", modelSource: "", modelColor: "#7E5C5C"});
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
                    case AppearanceMenu.ListIndex.BLUE_ACTION:
                        appController.changeAppearance(App.BLUE);
                        break;

                    case AppearanceMenu.ListIndex.RED_ACTION:
                        appController.changeAppearance(App.RED);
                        break;
                    }
                }
            }
        }
    }

    Custom.String {
        id: title
        anchors.top: topBarMenu.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 24
        font.pixelSize: 24
        font.bold: true
        color: "#FFFFFF"
        text: "Choose Application Skin"
    }

    ListView {
        id: listView
        anchors.top: title.bottom
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
