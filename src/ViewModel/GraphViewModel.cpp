#include "GraphViewModel.h"

#include <QVariant>

GraphViewModel::GraphViewModel(QObject *parent)
   : QObject(parent)
{
    m_graph = std::make_shared<Graph>();

    m_list = std::make_unique<VertexListViewModel>(m_graph);
}

VertexListViewModel *GraphViewModel::verticesList() const
{
    return m_list.get();
}

QVariantList GraphViewModel::edges() const
{
    QVariantList edges;

    for (const auto& edge: m_graph->edges())
    {
        QVariantList resultingEdge;

        for (const auto& vertex: edge)
            resultingEdge.append(vertex);

        edges.push_back(resultingEdge);
    }

    return edges;
}

int GraphViewModel::vertexCount() const
{
    return m_graph->vertices().size();
}

QVariantList GraphViewModel::findCliques() const
{
    QVariantList foundedCliques;

    for (const auto& clique: m_graph->cliques())
    {
        QString cliqueString = "{ ";

        QStringList vertices;
        for (const auto& vertex: clique)
            vertices.append(QString::number(vertex));

        cliqueString += vertices.join(", ");
        cliqueString += " }";
        foundedCliques.append(cliqueString);
    }

    return foundedCliques;
}

void GraphViewModel::addNewVertex()
{
    m_list->addVertex();
}

void GraphViewModel::deleteVertex(int v)
{
    m_list->deleteVertex(v);

    emit edgesChanged();
}

void GraphViewModel::addNewEdge(int u, int v)
{
    m_graph->addEdge(u, v);

    emit edgesChanged();
}

void GraphViewModel::deleteEdge(int u, int v)
{
    m_graph->deleteEdge(u, v);

    emit edgesChanged();
}

void GraphViewModel::clear()
{
    m_graph = std::make_unique<Graph>(0);
}
