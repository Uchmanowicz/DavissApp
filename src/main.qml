import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1 as QtLabs

import "ui/iconsMap.js" as JS
import "ui/Styles"
import "ui/Custom" as Custom

ApplicationWindow {
    id: app

//    width: OS_ANDROID ? Screen.desktopAvailableWidth :
//                        OS_WINDOWS ? Screen.desktopAvailableWidth * 0.3 :
//                                     Screen.desktopAvailableWidth * 0.5

//    height: OS_ANDROID ? Screen.desktopAvailableHeight :
//                         OS_WINDOWS ? Screen.desktopAvailableHeight * 0.7 :
//                                      Screen.desktopAvailableHeight * 0.8

//    width: Screen.desktopAvailableWidth * 0.2
//    height: Screen.desktopAvailableHeight * 0.75

//    width: Screen.desktopAvailableWidth
//    height: Screen.desktopAvailableHeight

    width: 360
    height: 703

    visible: true
    title: "DavissApp"
    color: "black"

    signal closeDialogs();

    onClosing: {
//        console.log("WIDTH", width, " HEIGHT:", height)
        if(stackView.isDialog) {
            close.accepted = false;
            app.closeDialogs();
            return;
        }

        if(stackView.depth > 1 && !stackView.isDialog){
            close.accepted = false;
            stackView.pop();
        }else{
            return;
        }
    }

    onActiveFocusControlChanged:  {
        if(activeFocusItem && activeFocusItem.objectName !== "StringInput") {
            Qt.inputMethod.hide();
        }
    }

    Shortcut {
        id: backShortcut
        sequence: StandardKey.Cancel
        onActivated: {
            callback();
        }

        property var callback: function(){};

        function resetCallback() {
            callback = function() {stackView.pop();}
        }
    }

    property alias styleApp: styleApp
    StylesApp {id: styleApp}

    property var iconsMap: JS.iconsMap
    FontLoader {id: iconsLoader; source: "qrc:///ui/Fonts/MaterialIcons-Regular.ttf"}

    StackView{
        id: stackView
        anchors.fill: parent

        initialItem: "qrc:///ui/Modules/Desktop/Desktop.qml"

        property bool isDialog: false
    }

    function popView(arg = "") {
        stackView.pop(arg);
    }

    function hideKeyboard() {
        Qt.inputMethod.hide();
    }

    function onBackShortcut(callback) {
        backShortcut.callback = function(){callback();};
    }

    function resetBackShortcut() {
        backShortcut.resetCallback();
    }

    function blockBackShortcut() {
        backShortcut.enabled = false;
        console.log(backShortcut.enabled)
    }

    function unblockBackShortCut() {
        backShortcut.enabled = true;
    }

    Custom.String {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 10
        text: APP_VERSION
        font.pixelSize: 10
        color: "#FFFFFF"
    }

    QtLabs.FileDialog {
        id: _holderFileDialog
        title: "Choose image"
        nameFilters: ["Image files (*.jpg *.jpeg *.png)"]

//        folder: QtLabs.StandardPaths.writableLocation(QtLabs.StandardPaths.DocumentsLocation)
        fileMode: QtLabs.FileDialog.OpenFile
        onAccepted: {

        }
    }
}


