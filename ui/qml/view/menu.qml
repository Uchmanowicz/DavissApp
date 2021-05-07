import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import "../myComponents"

Item {

    Image {
        id: imagePaper
        source: "qrc:/resources/logo/fire.png"
        anchors{
            top: imageTop.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
    }

    Rectangle{
        id: recTop
        width: parent.width
        height: imageTop.height
        anchors.top: parent.top
        anchors.left: parent.left
        color: "white"
    }

    Image {
        id: imageTop
        source: "qrc:/resources/logo/logo.jpg"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: 200

        height: 40
    }


    ColumnLayout{
        id: mainCol
        spacing: 3
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter


        Button{
            id: buttDepo
            highlighted: true
            Material.accent: Material.color(Material.Red, Material.Shade600)

            text: qsTr("<b>Depo</b>")

            onClicked: {
                dbController.qmlRefreshDepoDb()
                stackViewMain.push("depo.qml")
            }
        }
    }

    Image {
        id: buttSettings
        source: "qrc:/resources/button/buttSettings.png"
        width: 50
        height: 50

        anchors {
            bottom: parent.bottom
            left: parent.left

            leftMargin: 10
            bottomMargin: 10
        }

        MouseArea{
            anchors.fill: parent

            onClicked: {
                stackViewMain.push("settings.qml")
            }
        }

    }
}



