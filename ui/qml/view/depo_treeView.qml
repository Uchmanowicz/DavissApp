import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as C1

import "../myComponents"
import "../view"

Item {

    C1.TreeView{
        id: treeView
        anchors{
            top: toolBarTop.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        model: treeViewModel
        C1.TableViewColumn{
            role: "display"
            title: "Category"
            width: 100
        }
        C1.TableViewColumn{
            role: "display"
            title: "SubCategory2"
            width: 100
        }
    }

    ToolBar_m {
        id: toolBarTop
        anchors.top: parent.top

        buttBackArrowEnable: true

        onButtBackArrowClicked: stackViewMain.pop(null)
    }
}
