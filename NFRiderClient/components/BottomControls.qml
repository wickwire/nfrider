import QtQuick 2.0

Rectangle {
    id: bottomControls
    width: parent.width/1.2
    height: 50
    color: "olive"
    opacity: 0.7
    anchors.verticalCenter: parent.bottom
    anchors.verticalCenterOffset: -height/1.5
    anchors.horizontalCenter: parent.horizontalCenter
}
