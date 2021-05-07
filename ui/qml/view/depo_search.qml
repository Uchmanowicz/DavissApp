import QtQuick 2.0
import QtQuick.Controls 2.12

import "../myComponents"
import "../view"

Item {

    Button{
        text: "test"
        anchors.top: toolBarTop.bottom
    }

    ToolBar_m {
        id: toolBarTop
        anchors.top: parent.top

        buttBackArrowEnable: true

        onButtBackArrowClicked: stackViewMain.pop(null)
    }
}
