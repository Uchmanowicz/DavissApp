import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import "../../Custom" as Custom

Rectangle {
    id: control
    color: "#000000"

    property bool isActive: SwipeView.isCurrentItem

    signal back();

    onIsActiveChanged: {
        if(isActive) {
            app.onBackShortcut(function(){
                control.back();
            });
        }
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
            spacing: 0

            Custom.String {
                Layout.topMargin: 24
                text: "Name"
            }

            Custom.StringField {
                id: nameField
                Layout.topMargin: 16
                Layout.fillWidth: true
                Layout.preferredHeight: height
            }

            Custom.String {
                Layout.topMargin: 24
                text: "Category"
            }

            Custom.StringField {
                id: categoryField
                Layout.topMargin: 16
                Layout.fillWidth: true
                Layout.preferredHeight: height
            }

            Custom.Button {
                id: add
                Layout.topMargin: 40
                Layout.alignment: Qt.AlignRight
                Layout.preferredHeight: height
                Layout.preferredWidth: width
                Layout.minimumWidth: 150
                isSpecial: true
                text: "Add"

                onClicked: {
                    depotController.addItem(nameField.text, categoryField.text);
                }
            }
        }
    }

    Custom.TopBarMenu {
        id: topBarMenu
    }
}
