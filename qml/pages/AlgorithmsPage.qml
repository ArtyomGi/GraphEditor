import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    property var viewModel

    allowedOrientations: Orientation.All

    property var algorithmList: [
        {
            id: 1,
            name: qsTr("Cliques finder")
        }
    ]

    function executeAlgorithm(algorithm) {
        if (!algorithm)
            return

        if (algorithm.id === 1) {
            var cliques = viewModel.graphViewModel.findCliques()
            pageStack.animatorPush(Qt.resolvedUrl("CliqueViewPage.qml"), { cliquesList: cliques })
        }
    }

    SilicaListView {
        id: listView
        model: algorithmList
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Graph Algorithms")
        }
        delegate: BackgroundItem {
            id: delegate

            Label {
                x: Theme.horizontalPageMargin
                text: modelData.name
                anchors.verticalCenter: parent.verticalCenter
                color: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
            }
            onClicked: executeAlgorithm(modelData)
        }
        VerticalScrollDecorator {}
    }
}
