import QtQuick 2.15

QtObject {
    property QtObject red: QtObject {
        property color backgroundColor: "#667E5C5C"
        property color backgroundPressedColor: "#66C7C9CF"
        property color borderColor: "#7E5C5C"

        property color backgroudDialogColor: "#3D2121"

        property color spacerColor: "#44634444"
    }

    property QtObject blue: QtObject {
        property color backgroundColor: "#665C637E"
        property color backgroundPressedColor: "#66C7C9CF"
        property color borderColor: "#5C637E"

        property color backgroudDialogColor: "#21273D"

        property color spacerColor: "#445C637E"
    }
}
