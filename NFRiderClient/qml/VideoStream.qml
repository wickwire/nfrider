import QtQuick 2.0
import QtMultimedia 5.0

Item {
    MediaPlayer {
        id: mediaplayer
        source: "http://192.168.55.100:5004/go.mp4"
        autoPlay: true
        autoLoad: true
    }

    VideoOutput {
        anchors.fill: parent
        source: mediaplayer
    }

}
