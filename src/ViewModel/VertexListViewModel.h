#pragma once

#include <memory>

#include <QAbstractListModel>

#include "../Model/Graph.h"

class VertexListViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit VertexListViewModel(const std::shared_ptr<Graph>& graph, QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    int rowCount(const QModelIndex &parent) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addVertex();
    void addVertex(int v);
    void deleteVertex(int v);

private:
    QVector<size_t> m_vertexNumbers;
    std::shared_ptr<Graph> m_graph;
};
