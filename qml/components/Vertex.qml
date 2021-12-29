import QtQuick 2.6
import Sailfish.Silica 1.0

Rectangle {
    id: root

    property int number

    signal clicked
    signal deleteRequested

    radius: height / 2
    border.color: "black"
    border.width: 2
    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: width / 2
    Drag.hotSpot.y: height / 2


    Text {
        anchors.centerIn: parent
        text: number
    }

    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: parent
        drag.axis: Drag.XAndYAxis
        onClicked: root.clicked()
        onDoubleClicked: {
            var remorse = Remorse.popupAction(root, "The %1 vertex is going to be deleted".arg(number), function() {
                root.deleteRequested()
            })
        }
    }
}
