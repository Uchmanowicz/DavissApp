import QtQuick 2.15
import ui.types 1.0

Item {
    id: control
    property QtObject button: priv.button.standard.blue
    property QtObject buttonSpecial: priv.button.special.red
    property QtObject stringField: priv.stringField.blue
    property QtObject menuDelegate: priv.menuDelegate.blue
    property QtObject switchButton: priv.switchButton.blue
    property color topBar: priv.topBar.blue

    Connections {
        target: appController

        function onAppChanged() {
            let skinToSet = appController.ui_app.ui_appearance

            if(skinToSet === App.BLUE) {
                priv.setStyleBlue();
            }else if(skinToSet === App.RED) {
                priv.setStyleRed();
            }
        }
    }

    Item {
        id: priv

        property int currentSkin: -1

        property QtObject stringField: stringField
        property QtObject button: button
        property QtObject menuDelegate: menuDelegate
        property QtObject switchButton: switchButton


        property QtObject topBar: QtObject {
            property color red: "#7E5C5C"
            property color blue: "#2F3B59"
        }

        StylesStringField {id: stringField}
        StylesButton {id: button}
        StylesMenuDelegate {id: menuDelegate}
        StylesSwitch {id: switchButton}

        function setStyleBlue() {
            priv.currentSkin = App.BLUE;
            control.button = priv.button.standard.blue;
            control.buttonSpecial = priv.button.special.red;
            control.stringField = priv.stringField.blue;
            control.menuDelegate = priv.menuDelegate.blue;
            control.switchButton = priv.switchButton.blue;
            control.topBar = priv.topBar.blue;
        }

        function setStyleRed() {
            priv.currentSkin = App.RED;
            control.button = priv.button.standard.red;
            control.buttonSpecial = priv.button.special.blue;
            control.stringField = priv.stringField.red;
            control.menuDelegate = priv.menuDelegate.red;
            control.switchButton = priv.switchButton.red;
            control.topBar = priv.topBar.red;
        }
    }
}
