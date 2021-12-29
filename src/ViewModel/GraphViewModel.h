#pragma once

#include <memory>

#include <QObject>
#include <QVariant>

#include "../Model/Graph.h"
#include "VertexListViewModel.h"

class GraphViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(VertexListViewModel *verticesList READ verticesList CONSTANT)
    Q_PROPERTY(QVariantList edges READ edges NOTIFY edgesChanged)

public:
    explicit GraphViewModel(QObject *parent = nullptr);

    VertexListViewModel *verticesList() const;
    QVariantList edges() const;
    int vertexCount() const;

    Q_INVOKABLE QVariantList findCliques() const;

    Q_INVOKABLE void addNewVertex();
    Q_INVOKABLE void deleteVertex(int v);
    Q_INVOKABLE void addNewEdge(int u, int v);
    Q_INVOKABLE void deleteEdge(int u, int v);
    Q_INVOKABLE void clear();

signals:
    void edgesChanged();

private:
    std::shared_ptr<Graph> m_graph;
    std::unique_ptr<VertexListViewModel> m_list;
};
