import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../view"


Rectangle{
    id: toolBar
    width: parent.width
    height: parent.height * 0.07 > 50 ? parent.height * 0.07 : 50
    color: "grey"

    property bool buttBackArrowEnable: true
    property bool buttAddEnable: false
    property bool buttDeleteEnable: false
    property bool buttSearchEnable: false
    property bool buttTreeViewEnable: false
    property bool buttInfoEnable: false

    signal buttBackArrowClicked
    signal buttAddClicked
    signal buttDeleteClicked
    signal buttSearchClicked
    signal buttTreeViewClicked
    signal buttInfoClicked



    RowLayout{
        anchors.fill: parent

        Image {
            id: imageBack
            enabled: buttBackArrowEnable
            visible: buttBackArrowEnable
            source: "qrc:/resources/button/buttBack.png"
            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            Layout.preferredHeight: parent.height * 0.9
            Layout.preferredWidth: 30
            Layout.leftMargin: 5

            MouseArea{
                anchors.fill: parent
                onClicked: toolBar.buttBackArrowClicked()
            }
        }

        Item {
            Layout.fillWidth: true
        }


        Image {
            id: imageAdd
            enabled: buttAddEnable
            visible: buttAddEnable
            source: "qrc:/resources/button/buttAdd.png"
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight: parent.height * 0.9
            Layout.preferredWidth: 30


            MouseArea{
                anchors.fill: parent
                onClicked: toolBar.buttAddClicked()
            }
        }

        Image {
            id: imageDelete
            enabled: buttDeleteEnable
            visible: buttDeleteEnable
            source: "qrc:/resources/button/buttDelete.png"
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredHeight: parent.height * 0.9
            Layout.preferredWidth: 30


            MouseArea{
                anchors.fill: parent
                onClicked: toolBar.buttDeleteClicked()
            }
        }

        Image {
            id: imageTreeView
            enabled: buttTreeViewEnable
            visible: buttTreeViewEnable
            source: "qrc:/resources/button/buttTreeView.png"
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            Layout.preferredHeight: parent.height * 0.9
            Layout.preferredWidth: 30
            Layout.rightMargin: 5
            Layout.leftMargin: 20


            MouseArea{
                anchors.fill: parent
                onClicked: toolBar.buttTreeViewClicked()
            }
        }

        Image {
            id: imageSearch
            enabled: buttSearchEnable
            visible: buttSearchEnable
            source: "qrc:/resources/button/buttSearch.png"
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            Layout.preferredHeight: parent.height * 0.9
            Layout.preferredWidth: 30
            Layout.rightMargin: 5
            Layout.leftMargin: 20


            MouseArea{
                anchors.fill: parent
                onClicked: toolBar.buttSearchClicked()
            }
        }

        Image {
            id: imageInfo
            enabled: buttInfoEnable
            visible: buttInfoEnable
            source: "qrc:/resources/button/buttInfo.png"
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            Layout.preferredHeight: parent.height * 0.9
            Layout.preferredWidth: 40
            Layout.rightMargin: 5
            Layout.leftMargin: 20


            MouseArea{
                anchors.fill: parent
                onClicked: toolBar.buttInfoClicked()
            }
        }
    }

}

