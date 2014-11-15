import QtQuick 2.0
import "qrc:/components"

Item{
    id: spinnerLoader
    width: 100
    height:40

    Rectangle {
        id: spinner
        anchors.verticalCenter: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: 50
        height:10
        radius: 5
        color: "white"
        opacity: 1

        PropertyAnimation{
            running: true
            property: "rotation"
            target: spinner
            from: 0
            to: 360
            loops: Animation.Infinite
            duration: 500
        }
    }

    Text{
        anchors.verticalCenter: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Loading..."
        color: "white"
    }
}

