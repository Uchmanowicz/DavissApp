import QtQuick 2.15

//Rectangle {
//    id: control
//    anchors.fill: parent
//    color: "transparent"

//    property int borderWidth: 0
//    property color borderColor: "#00FFFFFF"

//    property int leftBorderWidth: borderWidth
//    property color leftBorderColor : borderColor

//    property int rightBorderWidth: borderWidth
//    property color rightBorderColor : borderColor


//    Rectangle {
//        id: topBorder
//        anchors{
//            top: parent.top
//            left: parent.left
//            right: parent.right
//        }
////        color: "transparent"
//        color: control.leftBorderColor
//        height: control.leftBorderWidth
//        radius: 6
//        //        border.width: control.leftBorderWidth
//        //        border.color: control.leftBorderColor
//    }

//    Rectangle {
//        id: leftBorder
//        //        anchors.fill: parent
//        //        color: "transparent"
//        //        border.width: control.rightBorderWidth
//        //        border.color: control.rightBorderColor

//        anchors{
//            left: parent.left
//            top: parent.top
//            bottom: parent.bottom
//        }
//        color: control.leftBorderColor
//        width: control.leftBorderWidth
//        radius: 6
//    }
//}

//Rectangle
//{

//    property bool commonBorder : true

//    property int lBorderwidth : 1
//    property int rBorderwidth : 1
//    property int tBorderwidth : 1
//    property int bBorderwidth : 1

//    property int borderWidth : 1

//    z : -1

//    property string borderColor : "white"

//    color: borderColor
//    radius: 5

//    anchors
//    {
//        left: parent.left
//        right: parent.right
//        top: parent.top
//        bottom: parent.bottom

//        topMargin    : commonBorder ? -borderWidth : -tBorderwidth
//        bottomMargin : commonBorder ? -borderWidth : -bBorderwidth
//        leftMargin   : commonBorder ? -borderWidth : -lBorderwidth
//        rightMargin  : commonBorder ? -borderWidth : -rBorderwidth
//    }
//}


Item
{
    property alias color: innerRect.color

    property alias borderColor : borderRect.color
    property int borderWidth: 0

    property int lBorderwidth : borderWidth
    property int rBorderwidth : borderWidth
    property int tBorderwidth : borderWidth
    property int bBorderwidth : borderWidth

    Rectangle
    {
        id: borderRect
        anchors.fill: parent
        radius: 6

        Rectangle
        {
            id: innerRect
            radius: 6

            anchors {
                fill: parent

                leftMargin: lBorderwidth
                rightMargin: 0
                topMargin: tBorderwidth
                bottomMargin: bBorderwidth
            }
        }
    }
}
