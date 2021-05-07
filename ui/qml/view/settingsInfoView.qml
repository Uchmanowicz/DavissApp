import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQml.Models 2.15

import "../myComponents"

Item {
    id: screenSettingsInfo

    // TEMPORARY SOLUTION
    Label{
        id: tempLabel

        anchors{
            left: parent.left
            top: toolBarTop.bottom
        }

        text: qsTr("<b>Database localization:</b>")
        font.pixelSize: 20
    }

    Label{
        id: tempLabelLocali

        anchors{
            left: parent.left
            top: tempLabel.bottom
            leftMargin: 10
        }

        text: dbController.databasePath
        wrapMode: Text.WrapAnywhere

    }

    ToolBar_m {
        id: toolBarTop
        anchors.top: parent.top

        buttBackArrowEnable: true

        onButtBackArrowClicked: stackViewMain.pop(null)

    }
}


