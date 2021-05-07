import QtQuick 2.15
import QtQuick.Layouts 1.12

Rectangle {
    id: control
    anchors.fill: parent
    color: "#80000000"
    opacity: 0.0
    visible: false

    property int contentHeight: 0
    property int contentWidth: 0

    signal showed()
    signal hidden()

    onVisibleChanged: {
        if(visible) {
            stackView.isDialog = true;
        }else {
            stackView.isDialog = false;
        }
    }

    Behavior on opacity {
        NumberAnimation {duration: 150}
    }

    function hide() {
        control.opacity = 0.0;
        control.visible = false;
    }

    function show() {
        control.showed();
        control.visible = true;
        control.opacity = 1.0;
    }

    Connections{
        target: app

        function onCloseDialogs() {
            control.hide();
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: app.hideKeyboard()
    }

    Rectangle {
        id: background
        anchors.centerIn: parent
        width: control.contentWidth
        height: control.contentHeight
        radius: 6
        color: app.styleApp.menuDelegate.backgroudDialogColor
    }
}
