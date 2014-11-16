import QtQuick 2.2
import QtQuick.Controls 1.1
import "qrc:/components"

ApplicationWindow {
    visible: true
    width: 1366
    height: 668
    color: "black"

    //place the video screen in the background
//    VideoScreen{
//        id: videoScreen
//    }

    VideoStream{
        id: stream
        width: 600
        height: 600
        anchors.centerIn: parent
    }

    //place the heads up display (HUD) in the foreground
    HUD{
        id: hud   
    }


    ScreenFrame{
        id: centralFrame
        height: stream.height/1.22
        width: 20
        anchors.horizontalCenter: stream.right
        anchors.verticalCenter: stream.verticalCenter
    }
}
