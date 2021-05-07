import QtQuick 2.15
import QtGraphicalEffects 1.0

MouseArea {
  id: control
  property bool isSpecial: false

  property alias iconSource: icon.source
  property alias text: label.text
  property alias layoutDirection: contentRow.layoutDirection
  property alias dropShadow: shadow.visible
  property int alignment: Qt.AlignHCenter
  property bool animateScale: true
  property bool shadowEnabled: true
  property alias fontPixel: label.font.pixelSize
  property QtObject style: control.isSpecial ? app.styleApp.buttonSpecial : app.styleApp.button

  height: 46
  width: text.length > 0 || iconSource > height ? contentRow.implicitWidth + 28 : height
//  enabled: stackView.animationEnded

  DropShadow {
    id: shadow
    anchors.fill: parent
    source: background
    visible: !control.pressed && control.enabled && control.shadowEnabled
    horizontalOffset: 0
    verticalOffset: 6
    radius: 12
    samples: 17
    color: "#33000000"
  }

  Rectangle { //background
    id: background
    anchors.centerIn: parent
    width: parent.width
    height: parent.height
    scale: control.pressed && animateScale ? 0.95 : 1
    radius: 4
    color: {
      if(control.enabled === false)
        return control.style.backgroundDisabledColor
      if(control.pressed)
        return control.style.backgroundPressedColor
      return control.style.backgroundNormalColor
    }

    Behavior on scale {
      NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
    }
  } //end background

  Row {
    id: contentRow
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: control.alignment === Qt.AlignHCenter ? parent.horizontalCenter : undefined
    anchors.left: control.alignment === Qt.AlignLeft ? parent.left : undefined
    anchors.right: control.alignment === Qt.AlignRight ? parent.right : undefined
    anchors.leftMargin: control.alignment === Qt.AlignLeft ? 10 : 0
    spacing: 10

    Icon {
      id: icon
      anchors.verticalCenter: parent.verticalCenter

      color: {
        if(control.enabled === false)
          return control.style.iconDisabledColor
        if(control.pressed)
          return control.style.iconPressedColor
        return control.style.iconNormalColor
      }
    }

    Text {
      id: label
      anchors.verticalCenter: parent.verticalCenter
      anchors.verticalCenterOffset: 2
//      font.family: poppinsSemiBold.name
      font.bold: true
      font.pixelSize: 14
      font.capitalization: Font.AllUppercase
      color: {
        if(control.enabled === false)
          return control.style.textDisabledColor
        if(control.pressed)
          return control.style.textPressedColor
        return control.style.textNormalColor
      }
    }
  }
}
