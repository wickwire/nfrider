import QtQuick 2.2
import QtQuick.Controls 1.1
import "qrc:/components"

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    color: "black"

    //place the video stream in the background
    VideoStream{
        id: stream
        anchors.fill: parent
    }

    //place the heads up display (HUD) in the foreground
    HUD{
        id: hud
    }

}
