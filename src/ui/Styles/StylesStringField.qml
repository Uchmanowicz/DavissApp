import QtQuick 2.15

QtObject {
    property QtObject red: QtObject {
        property color background: "#667E5C5C"
        property color borderColor: "#7E5C5C"
        property color focusedBorderColor: "#FFFFFF"
        property color cursorColor: "#FFFFFF"
        property color placeholderTextColor: "#949494"
        property color textColor: "#FFFFFF"
        property color selectedTextColor: "#FFFFFF"
        property color selectionColor: "#00619D"
    }

    property QtObject blue: QtObject {
        property color background: "#665C6A7E"
        property color borderColor: "#5C637E"
        property color focusedBorderColor: "#FFFFFF"
        property color cursorColor: "#FFFFFF"
        property color placeholderTextColor: "#949494"
        property color textColor: "#FFFFFF"
        property color selectedTextColor: "#FFFFFF"
        property color selectionColor: "#A3A4A5"
    }
}
