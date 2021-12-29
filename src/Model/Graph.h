#pragma once

#include <map>
#include <set>
#include <vector>

using Vertex = size_t;
using Edge = std::set<Vertex>;

class Graph
{
public:
    Graph(size_t N = 0)
    {
        for (Vertex i = 1; i <= N; ++i)
        {
            graph.emplace(i, std::set<Vertex>());
        }

        lastVertex = N;
    }

    void addVertex();
    void deleteVertex(Vertex v);
    void addEdge(Vertex u, Vertex v);
    void deleteEdge(Vertex u, Vertex v);

    std::set<Vertex> Adj(Vertex u) const;
    std::set<Vertex> vertices() const;
    std::set<Edge> edges() const;

    std::set<std::set<Vertex>> cliques() const;

private:
    std::map<Vertex, std::set<Vertex>> graph;
    Vertex lastVertex;
};

class CliqueAlgorithm
{
public:
    CliqueAlgorithm(const Graph& graph):
        G(graph) {}

    std::set<std::set<Vertex>> calculateCliques();

private:
    void clique(std::set<Vertex> N, std::set<Vertex> D);
    void explore(Vertex vertex, std::set<Vertex>& N, std::set<Vertex>& D);

private:
    const Graph& G;
    std::set<Vertex> S;
    std::set<std::set<Vertex>> cliques;
};
