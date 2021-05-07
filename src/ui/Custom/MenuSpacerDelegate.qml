import QtQuick 2.15

Item {
    id: control
    width: ListView.view.width
    height: ornament.height + 10

    Rectangle {
        id: ornament
        anchors.centerIn: parent
        width: parent.width - 20
        height: 12
        radius: 12
        color: app.styleApp.menuDelegate.spacerColor
    }
}
