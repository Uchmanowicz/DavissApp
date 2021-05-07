import QtQuick 2.15
import QtQuick.Layouts 1.12

Rectangle {
    id: delegate
    width: ListView.view.width
    anchors.bottomMargin: 24
    height: 60
    radius: 6
    border.width: 1
    border.color: app.styleApp.menuDelegate.borderColor
    color: mouseArea.pressed && delegate.enableAnimation ? app.styleApp.menuDelegate.backgroundPressedColor : app.styleApp.menuDelegate.backgroundColor

    Behavior on color {
        ColorAnimation {duration: 100}
    }

    property alias text: title.text
    property string iconSource: ""
    property color iconColor: "#FFFFFF"
    property bool enableAnimation: true

    signal clicked()

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 12
        anchors.verticalCenter: parent.verticalCenter
        spacing: 16

        Icon {
            id: icon
            Layout.fillHeight: true
            Layout.preferredWidth: height
            Layout.topMargin: 10
            Layout.bottomMargin: 10
            size: height
            source: delegate.iconSource.length > 6 ? "" : delegate.iconSource
            color: delegate.iconColor
            visible: !(delegate.iconSource.length > 6 || delegate.iconSource.length < 1)
        }

        Image {
            id: image
            Layout.fillHeight: true
            Layout.preferredWidth: height
            Layout.topMargin: 10
            Layout.bottomMargin: 10
            source: delegate.iconSource.length > 6 ? delegate.iconSource : ""
            visible: delegate.iconSource.length > 6
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: height
            Layout.topMargin: 10
            Layout.bottomMargin: 10
            radius: 6
            visible: !icon  .visible && !image.visible
            color: delegate.iconColor
        }

        String {
            id: title
            Layout.alignment: Qt.AlignVCenter
            font.pixelSize: 16
            color: "#FFFFFF"
        }

        Item {
            Layout.fillWidth: true
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: delegate.clicked()
    }
}
