#include "VertexListViewModel.h"


VertexListViewModel::VertexListViewModel(const std::shared_ptr<Graph>& graph, QObject *parent)
    : QAbstractListModel(parent), m_graph(graph)
{
    for (const auto& vertex: m_graph->vertices())
        m_vertexNumbers.append(vertex);
}

QVariant VertexListViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    std::vector<int> vertices;
    for (const auto& vertex: m_graph->vertices())
        vertices.push_back(vertex);

    if (role == Qt::UserRole)
        return vertices.at(index.row());

    return QVariant();
}

void VertexListViewModel::addVertex()
{
    int row = m_graph->vertices().size();

    beginInsertRows(QModelIndex(), row, row);
    m_graph->addVertex();
    endInsertRows();
}

void VertexListViewModel::addVertex(const int v)
{
    // TODO!!!
//    int row = m_graph->vertices().size();

//    beginInsertRows(QModelIndex(), row, row);
//    m_graph->vertices().emplace(v);
    //    endInsertRows();
}

void VertexListViewModel::deleteVertex(int v)
{
    QVector<int> vertices;
    for (const auto& vertex: m_graph->vertices())
        vertices.push_back(vertex);

    int row = vertices.indexOf(v);

    beginRemoveRows(QModelIndex(), row, row);
    m_graph->deleteVertex(v);
    endRemoveRows();
}

Qt::ItemFlags VertexListViewModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
        return (QAbstractListModel::flags(index)|Qt::ItemIsDragEnabled);

    return Qt::ItemIsDropEnabled;
}

bool VertexListViewModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;

    if (row >= static_cast<int>(m_graph->vertices().size()) || row + count <= 0)
        return false;

    QVector<int> vertices;
    for (const auto& vertex: m_graph->vertices())
        vertices.push_back(vertex);

    int beginRow = qMax(0, row);
    int endRow = qMin(row + count - 1, static_cast<int>(m_graph->vertices().size() - 1));

    beginRemoveRows(parent, beginRow, endRow);

    while (beginRow <= endRow) {
        vertices.removeAt(beginRow);
        ++beginRow;
    }

    endRemoveRows();

    // TODO!!!
//    QVector<int> vertices;
//    for (const auto& vertex: m_graph->vertices())
//        vertices.push_back(vertex);

    return true;
}

int VertexListViewModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_graph->vertices().size();
}

QHash<int, QByteArray> VertexListViewModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole] = "number";
    return roles;
}
