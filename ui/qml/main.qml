import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import "../qml/myComponents"
import "../qml/view"



ApplicationWindow {
    id: appWindowMain



    width: OS_ANDROID ? Screen.desktopAvailableWidth :
                        OS_WINDOWS ? Screen.desktopAvailableWidth * 0.3 :
                                     Screen.desktopAvailableWidth * 0.5

    height: OS_ANDROID ? Screen.desktopAvailableHeight :
                         OS_WINDOWS ? Screen.desktopAvailableHeight * 0.5 :
                                      Screen.desktopAvailableHeight * 0.8

    visible: true
    title: qsTr("DavissApp")

    color: "black"

    onClosing: {
        if(stackViewMain.depth > 1){
            close.accepted = false
            stackViewMain.pop();
        }else{
            return;
        }
    }


    User_m {
        id: user
        userName: settingsController.qmlUserName

        onUserNameChanged: {
            if(userName === "NONE")
            {
                isLogged = false
            }else {
                isLogged = true
            }
        }
    }


    StackView{
        id: stackViewMain
        anchors.fill: parent

        initialItem: "view/menu.qml"
    }



}
