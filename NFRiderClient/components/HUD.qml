import QtQuick 2.0

Rectangle{

    focus: true

    Keys.onPressed: {
        if ((event.key == Qt.Key_Up && event.isAutoRepeat == false))
            console.log("Key UP pressed")
    }

    Keys.onReleased: {
        if ((event.key == Qt.Key_Up && event.isAutoRepeat == false))
            console.log("Key UP released")
    }

    anchors.fill: parent
    color: "transparent"

    BottomControls{
        id: bottomcontrols
    }

    TopPager{
        id: toppager
    }
}
