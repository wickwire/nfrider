import QtQuick 2.0
import QtMultimedia 5.0
import "qrc:/components"

Item {

    Loader{
        id: spinnerLoader
        anchors.centerIn: parent
    }

    MediaPlayer {
        id: mediaplayer
        source: "http://192.168.55.100:5007/go7.mp4" //loki passthrough - A20
        //source: "http://192.168.55.100:5004/go.mp4" //loki passthrough - A10
        //source: "http://192.168.55.119:1337" //cubie direct connection (node) - A20
        //source: "udp://@:1234" //cubie direct connection (node) - A20
        autoPlay: true
        autoLoad: true

        Component.onCompleted: {
            //place the loader
            spinnerLoader.source = "Spinner.qml"
        }

        onHasVideoChanged: {
            console.log("changed!"); spinnerLoader.destroy();
        }
    }

    VideoOutput {
        anchors.fill: parent
        source: mediaplayer
    }
}
