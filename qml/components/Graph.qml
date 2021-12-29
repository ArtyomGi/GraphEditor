import QtQuick 2.0
import QtQuick.Particles 2.0


Item {
    id: root

    property var viewModel
    property bool edgeAdditionMode: false

    signal vertexClicked(int number)

    property var newEdgeVertex
    onVertexClicked: {
        if (edgeAdditionMode) {
            if (!newEdgeVertex) {
                newEdgeVertex = number
            }
            else {
                viewModel.addNewEdge(newEdgeVertex, number)
                newEdgeVertex = null
            }
        }
    }

    Repeater {
        id: edges
        model: viewModel && viewModel.edges
        delegate: Line {
            id: line

            property var vertex1
            property var vertex2

            x1: vertex1 ? vertex1.x + vertex1.width / 2 : 0
            y1: vertex1 ? vertex1.y + vertex1.height / 2 : 0
            x2: vertex2 ? vertex2.x + vertex2.width / 2 : 0
            y2: vertex2 ? vertex2.y + vertex2.height / 2 : 0

            onDeleteRequested: {
                if (viewModel)
                    viewModel.deleteEdge(modelData[0], modelData[1])
            }

            Component.onCompleted: {
                vertex1 = vertices.vertexByNumber(modelData[0])
                vertex2 = vertices.vertexByNumber(modelData[1])
            }
        }
    }

    Repeater {
        id: vertices
        model: viewModel && viewModel.verticesList

        function vertexByNumber(number) {
            for (var i = 0; i < count; ++i) {
                var vertex = itemAt(i)
                if (vertex.number === number)
                    return vertex
            }
        }

        delegate: Vertex {
            number: model.number
            x: 75
            y: 75
            height: 60
            width: 60

            onClicked: root.vertexClicked(number)
            onDeleteRequested: viewModel.deleteVertex(number)
        }
    }
}
