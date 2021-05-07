import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.15

import "../myComponents"
import "../view"

Item {
    id: screen

    transitions: [
        Transition {
            NumberAnimation {
                target: screenLayout
                property: "x"
                easing.type: Easing.OutBack
                duration: 600
            }

        }
    ]

    states: [
        State {
            name: "view1"
            PropertyChanges {
                target: screenLayout
                x: -appWindowMain.width

            }
        },

        State {
            name: "view2"
            PropertyChanges {
                target: screenLayout
                x: -2 * appWindowMain.width

            }
        }
    ]


    Row{
        id: screenLayout
        anchors.top: toolBarTop.bottom

        ListView{
            id: listViewCategory
            width: screen.width
            height: screen.height - toolBarTop.height
            model: dbController.qmlDepoCategoryList

            delegate: Image{
                width: parent.width
                height: 100

                Button {
                    text: "<b>" + dbController.qmlDepoCategoryList[index] + "</b>"
                    anchors {
                        left: parent.left
                        right: arrowNext.left
                        verticalCenter: parent.verticalCenter
                        leftMargin: 5
                        rightMargin: 5
                    }
                    height: 90
                    font.pixelSize: 20

                    onClicked: {
                        depoController.qmlSetDepoCategoryName(dbController.qmlDepoCategoryList[index])
                        screen.state = "view1"
                    }
                }

                Image {
                    id: arrowNext
                    source: "qrc:/resources/button/buttDoubleArrowWhite.png"
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 1
                    height: 80

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            depoController.qmlSetDepoCategoryName(dbController.qmlDepoCategoryList[index])
                            screen.state = "view1"
                        }
                    }
                }
            }
        }

        ListView{
            id: listViewSubCategory1
            width: screen.width
            height: screen.height - toolBarTop.height
            model: dbController.qmlDepoCategoryList

            delegate: Image{
                width: parent.width
                height: 100


                Image {
                    id: arrowPrevSub1
                    source: "qrc:/resources/button/buttDoubleLeftArrowWhite.png"
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 1
                    height: 80

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            depoController.qmlSetDepoCategoryName("NONE")
                            screen.state = ""
                        }
                    }
                }

                Button {
                    text: "<b>1" + dbController.qmlDepoCategoryList[index] + "</b>"
                    anchors {
                        left: arrowPrevSub1.right
                        right: arrowNextSub1.left
                        verticalCenter: parent.verticalCenter
                        leftMargin: 5
                        rightMargin: 5
                    }
                    height: 90
                    font.pixelSize: 20

                    onClicked: {
                        depoController.qmlSetDepoSub1CatName(dbController.qmlDepoCategoryList[index])
                        screen.state = "view2"
                    }
                }

                Image {
                    id: arrowNextSub1
                    source: "qrc:/resources/button/buttDoubleArrowWhite.png"
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 1
                    height: 80

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            depoController.qmlSetDepoSub1CatName(dbController.qmlDepoCategoryList[index])
                            screen.state = "view2"
                        }
                    }
                }
            }
        }


        ListView{
            id: listViewSubCategory2
            width: screen.width
            height: screen.height - toolBarTop.height
            //anchors.top: toolBarTop.bottom
            //anchors.horizontalCenter: parent.horizontalCenter
            model: dbController.qmlDepoCategoryList

            delegate: Image{
                width: parent.width
                height: 100


                Image {
                    id: arrowPrevSub2
                    source: "qrc:/resources/button/buttDoubleLeftArrowWhite.png"
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 1
                    height: 80

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            depoController.qmlSetDepoSub1CatName("NONE")
                            screen.state = "view1"
                        }
                    }
                }

                Button {
                    text: "<b>2" + dbController.qmlDepoCategoryList[index] + "</b>"
                    anchors {
                        left: arrowPrevSub2.right
                        right: arrowNextSub2.left
                        verticalCenter: parent.verticalCenter
                        leftMargin: 5
                        rightMargin: 5
                    }
                    height: 90
                    font.pixelSize: 20

                    onClicked: {
                        //depoController.qmlSetDepoSub1CatName(dbController.qmlDepoCategoryList[index])
                        screen.state = "view3"
                    }
                }

                Image {
                    id: arrowNextSub2
                    source: "qrc:/resources/button/buttDoubleArrowWhite.png"
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 1
                    height: 80

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            //depoController.qmlSetDepoSub1CatName(dbController.qmlDepoCategoryList[index])
                            screen.state = "view3"
                        }
                    }
                }
            }
        }
    }

    ToolBar_m {
        id: toolBarTop
        anchors.top: parent.top

        buttBackArrowEnable: true
        buttAddEnable: true
        buttDeleteEnable: true
        buttSearchEnable: true
        buttTreeViewEnable: true


        onButtBackArrowClicked: {
            depoController.qmlClearAllFilteres()
            stackViewMain.pop(null)
        }
        onButtAddClicked: stackViewMain.pop()
        onButtDeleteClicked: stackViewMain.pop()
        onButtTreeViewClicked: stackViewMain.push("../view/depo_treeView.qml")
        onButtSearchClicked: stackViewMain.push("../view/depo_search.qml")



    }


}


