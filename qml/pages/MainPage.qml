import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {
    id: page

    property var viewModel

    allowedOrientations: Orientation.All

    Component {
        id: deleteDialog

        Dialog {
            Column {
                spacing: 10
                width: page.width
                DialogHeader {}
                TextField {
                    id: vertexNumber
                }
            }
            onAccepted: {
                if (viewModel)
                    viewModel.graphViewModel.deleteVertex(parseInt(vertexNumber.text))
            }
        }
    }

    SilicaFlickable {
        anchors.fill: parent

         PullDownMenu {
            MenuItem {
                text: qsTr("Algorithms")
                onClicked: pageStack.animatorPush(Qt.resolvedUrl("AlgorithmsPage.qml"), { viewModel: page.viewModel })
            }
        }

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingMedium

            Row {
                id: firstRow
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.paddingMedium

                Button {
                    text: qsTr("Add new vertex")
                    onClicked: viewModel.graphViewModel.addNewVertex()
                }

                Button {
                    text: qsTr("Delete vertex")
                    onClicked: pageStack.push(deleteDialog)
                }
            }

            Row {
                id: secondRow
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.paddingMedium

                Button {
                    text: qsTr("Edge addition mode")
                    down: graph.edgeAdditionMode
                    onClicked: graph.edgeAdditionMode = !graph.edgeAdditionMode
                }
            }

            Graph {
                id: graph
                anchors {
                    top: secondRow.bottom
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                viewModel: page.viewModel && page.viewModel.graphViewModel
            }
        }
    }
}
