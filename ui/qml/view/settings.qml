import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

import "../myComponents"
import "../view"

Item {
    id: screenSettings

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


    ScrollView{
        id: scrollView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: toolBarTop.bottom
        anchors.bottom: parent.bottom

        clip: true

        ColumnLayout{
            id: mainColumn
            width:  scrollView.width


            Rectangle{
                id: rectLogin
                Layout.preferredWidth: parent.width * 0.95
                Layout.preferredHeight:  columnLogin.height
                Layout.alignment: Qt.AlignHCenter
                Layout.margins: 10

                radius: 10
                border.width: 2
                border.color: "grey"
                color: "transparent"

                ColumnLayout{
                    id: columnLogin
                    width: parent.width
                    Layout.alignment: Qt.AlignHCenter
                    Layout.margins: 10

                    ColumnLayout{
                        id: columnLoginData
                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillWidth: true

                        visible: !user.isLogged
                        enabled: !user.isLogged

                        Label{
                            id: labelLogin
                            Layout.alignment: Qt.AlignHCenter
                            Layout.topMargin: 5

                            text: qsTr("<b>Login:</b>")
                        }

                        TextField{
                            id: fieldLogin
                            Layout.alignment: Qt.AlignHCenter
                            Layout.preferredWidth: rectLogin.width  * 0.90

                            placeholderText: qsTr("USE THIS: test@test.test")
                        }

                        Label{
                            id: labelPassword
                            Layout.alignment: Qt.AlignHCenter

                            text: qsTr("<b>Password:</b>")
                        }

                        TextField{
                            id: fieldPassword
                            Layout.preferredWidth: rectLogin.width  * 0.90
                            Layout.alignment: Qt.AlignHCenter

                            placeholderText: qsTr("USE THIS: testPassword")
                            echoMode: TextInput.Password

                        }
                    }

                    Label{
                        id: labelLoginErr

                        property bool isFirstLogin: true
                        property bool animationEnable:  !user.isLogged

                        Layout.alignment: Qt.AlignHCenter
                        visible: user.isLoggingProgress ? false :
                                                          isFirstLogin ? false :
                                                                         !user.isLogged

                        color: "red"
                        text: qsTr("<b>Wrong user or password !</b>")
                        font.pixelSize: 15

                        SequentialAnimation on color {
                            running: labelLoginErr.animationEnable
                            loops: Animation.Infinite

                            ColorAnimation  {  to: "white"; duration: 500 }
                            ColorAnimation  {  to: "red";  duration: 500 }
                        }
                    }

                    Label{
                        id: labelLoggedSentence
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                        visible: user.isLogged
                        enabled: user.isLogged

                        color:  "orange"
                        text: qsTr("Hello " + user.userName +", your daily sentense:")
                    }

                    BusyIndicator{
                        id: busyIndi
                        Layout.alignment: Qt.AlignHCenter

                        running: user.isLoggingProgress
                        visible: user.isLoggingProgress
                    }

                    Button{
                        id: buttLogin
                        width: 150
                        Layout.alignment: Qt.AlignHCenter

                        enabled: !user.isLoggingProgress
                        text: user.isLogged ? qsTr("<b>Sign out</b>") : qsTr("<b>Sign in</b>")
                        highlighted: user.isLogged ? true : false
                        Material.accent: user.isLogged ? Material.color(Material.Red, Material.Shade600)
                                                       : Material.color(Material.Grey, Material.Shade600)

                        onClicked: {
                            labelLoginErr.isFirstLogin = false

                            if(!user.isLogged)
                            {
                                settingsController.qmlSignIn(fieldLogin.text.toString(), fieldPassword.text.toString())
                            }else{
                                settingsController.qmlSignOut()
                                fieldLogin.text = ""
                                fieldPassword.text = ""
                                labelLoginErr.isFirstLogin = true
                            }
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
        buttInfoEnable: true

        onButtBackArrowClicked: stackViewMain.pop(null)
        onButtInfoClicked: stackViewMain.push("../view/settingsInfoView.qml")
    }
}
