import QtQuick 2.0

Rectangle{
    id: topPager
    width: parent.width/1.4
    height: 50
    color: "red"
    opacity: 0.7
    anchors.verticalCenter: parent.top
    anchors.verticalCenterOffset: height/1.5
    anchors.horizontalCenter: parent.horizontalCenter
}
