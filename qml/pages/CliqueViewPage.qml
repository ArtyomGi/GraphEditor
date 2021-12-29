import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    property var cliquesList

    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        model: cliquesList
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Founded cliques")
        }
        delegate:  Label {
            x: Theme.horizontalPageMargin
            text: modelData
            color: Theme.primaryColor
        }
        VerticalScrollDecorator {}
    }
}
