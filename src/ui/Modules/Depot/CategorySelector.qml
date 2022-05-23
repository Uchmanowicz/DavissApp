import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15
import "../../Custom" as Custom

Rectangle {
    id: control
    color: "#000000"

    state: "0";

    states: [
        State {
            name: "0"
        },
        State {
            name: "1"
        },
        State {
            name: "2"
        }
    ]

    property bool isActive: SwipeView.isCurrentItem

    onIsActiveChanged: {
        if(isActive) {
            app.onBackShortcut(function(){
                if(control.state === "0") {
                    app.popView();
                }else {
                    control.state = parseInt(control.state) - 1;
                }
            });
        }
    }

    Component.onDestruction: {
        app.resetBackShortcut();
    }

    Flickable {
        id: flickable
        anchors {
            fill: parent
            top: topBarMenu.bottom
            topMargin: 32
        }
        leftMargin: 32
        rightMargin: 32
        topMargin: 32
        clip: true
        contentHeight: contentCol.implicitHeight + 32

        ColumnLayout {
            id: contentCol
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
            spacing: 32

            Repeater {
                model: depotController.ui_categoriesLevelMap[control.state]
                Layout.fillWidth: true

                delegate: Custom.String {
                    Layout.fillWidth: true
                    text: modelData

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            control.state = parseInt(control.state) + 1;
                        }
                    }

                }
            }
        }
    }

    Custom.TopBarMenu {
        id: topBarMenu
    }

}
