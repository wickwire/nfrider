import QtQuick 2.0
import QtGraphicalEffects 1.0
import "qrc:/components"

Rectangle{
    id: screenCanvas
    anchors.centerIn: parent
    width: 800
    height: 668
    color: "transparent"

    Rectangle{
        id: screenFrame
        width: screenCanvas.width/1.2
        height: screenCanvas.height/1.2
        anchors.centerIn: parent
        clip: true
        color: "transparent"

        VideoStream{
            id: stream
            width: screenCanvas.width
            height: screenCanvas.height
            anchors.centerIn: parent
        }
    }


}



