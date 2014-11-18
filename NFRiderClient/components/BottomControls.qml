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

    signal riderDirection(string directionKey);
    focus: true

    Keys.onPressed: {
        if ((event.key == Qt.Key_Up && event.isAutoRepeat == false))
        {
            console.log("Key UP pressed");
            event.accepted = true;
            sshclient.onDirectionPressed("forwardON");
        }
        else if ((event.key == Qt.Key_Down && event.isAutoRepeat == false))
        {
            console.log("Key DOWN pressed");
            event.accepted = true;
            sshclient.onDirectionPressed("reverseON");
        }
        else if ((event.key == Qt.Key_Right && event.isAutoRepeat == false))
        {
            console.log("Key RIGHT pressed");
            event.accepted = true;
            sshclient.onDirectionPressed("rightON");
        }
        else if ((event.key == Qt.Key_Left && event.isAutoRepeat == false))
        {
            console.log("Key LEFT pressed");
            event.accepted = true;
            sshclient.onDirectionPressed("leftON");
        }
    }

    Keys.onReleased: {
        if ((event.key == Qt.Key_Up && event.isAutoRepeat == false))
        {
            console.log("Key UP released");
            event.accepted = true;
            sshclient.onDirectionReleased("forwardOFF");
        }
        else if ((event.key == Qt.Key_Down && event.isAutoRepeat == false))
        {
            console.log("Key DOWN released");
            event.accepted = true;
            sshclient.onDirectionReleased("reverseOFF");
        }
        else if ((event.key == Qt.Key_Right && event.isAutoRepeat == false))
        {
            console.log("Key RIGHT released");
            event.accepted = true;
            sshclient.onDirectionReleased("rightOFF");
        }
        else if ((event.key == Qt.Key_Left && event.isAutoRepeat == false))
        {
            console.log("Key LEFT released");
            event.accepted = true;
            sshclient.onDirectionReleased("leftOFF");
        }
    }
}
