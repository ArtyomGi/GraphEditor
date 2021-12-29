#include "Graph.h"

#include <algorithm>
#include <iterator>

#include <iostream>


void Graph::addVertex()
{
    graph.emplace(++lastVertex, std::set<Vertex>());
}

void Graph::addEdge(Vertex u, Vertex v)
{
    if (graph.find(u) == graph.cend() || graph.find(v) == graph.cend())
        throw "Vertice should be less than number of vertices";

    graph[u].insert(v);
    graph[v].insert(u);
}

void Graph::deleteEdge(Vertex u, Vertex v)
{
    if (graph.find(u) == graph.cend() || graph.find(v) == graph.cend())
        throw "Vertice should be less than number of vertices";

    graph[u].erase(v);
    graph[v].erase(u);
}

void Graph::deleteVertex(Vertex v)
{
    auto found = graph.find(v);
    if (found == graph.cend())
        throw "Vertice should be less than number of vertices";

    if (v == lastVertex)
        --lastVertex;

    graph.erase(found);

    for (auto& pairs: graph)
        pairs.second.erase(v);
}

std::set<Vertex> Graph::Adj(Vertex u) const
{
    if (graph.find(u) == graph.cend())
        throw "Vertice should be less than number of vertices";

    return graph.at(u);
}

std::set<Vertex> Graph::vertices() const
{
    std::set<Vertex> V;

    for (const auto& pairs: graph)
        V.insert(pairs.first);

    return V;
}

std::set<Edge> Graph::edges() const
{
    std::set<Edge> edges;

    for (const auto& pairs: graph)
    {
        for (const auto& vertex: pairs.second)
            edges.emplace(std::set<Vertex>({ pairs.first, vertex }));
    }

    return edges;
}

std::set<std::set<Vertex>> Graph::cliques() const
{
    CliqueAlgorithm cliqueAlg(*this);
    return cliqueAlg.calculateCliques();
}


std::set<std::set<Vertex>> CliqueAlgorithm::calculateCliques()
{
    clique(G.vertices(), {});

    return cliques;
}

void CliqueAlgorithm::clique(std::set<Vertex> N, std::set<Vertex> D)
{
    std::set<Vertex> ND;

    std::set_union(N.begin(), N.end(),
        D.begin(), D.end(),
        std::inserter(ND, ND.begin()));

    if (ND.empty())
    {
        cliques.insert(S);
        return;
    }

    if (N.empty())
        return;

    Vertex f = *ND.begin();
    size_t maxCardinality = G.Adj(f).size();

    for (const Vertex v : ND)
    {
        std::set<Vertex> Adj = G.Adj(v);

        std::set<Vertex> NintersAdj;
        std::set_intersection(N.begin(), N.end(),
            Adj.begin(), Adj.end(),
            std::inserter(NintersAdj, NintersAdj.begin()));

        size_t intersCardinality = NintersAdj.size();
        if (intersCardinality > maxCardinality)
        {
            maxCardinality = intersCardinality;
            f = v;
        }
    }

    if (N.find(f) != N.end())
        explore(f, N, D);

    std::set<Vertex> V = G.vertices();
    std::set<Vertex> Adjf = G.Adj(f);

    std::set<Vertex> VdiffAdj;
    std::set_difference(V.begin(), V.end(),
        Adjf.begin(), Adjf.end(),
        std::inserter(VdiffAdj, VdiffAdj.begin()));

    std::set<Vertex> NintersectDiff;
    std::set_intersection(N.begin(), N.end(),
        VdiffAdj.begin(), VdiffAdj.end(),
        std::inserter(NintersectDiff, NintersectDiff.begin()));

    while (!NintersectDiff.empty())
    {
        Vertex v = *NintersectDiff.begin();
        explore(v, N, D);
        NintersectDiff.erase(v);
    }
}

void CliqueAlgorithm::explore(Vertex vertex, std::set<Vertex>& N, std::set<Vertex>& D)
{
    N.erase(vertex);
    S.insert(vertex);

    std::set<Vertex> Adj = G.Adj(vertex);

    std::set<Vertex> NintersectAdj;
    std::set_intersection(N.begin(), N.end(),
        Adj.begin(), Adj.end(),
        std::inserter(NintersectAdj, NintersectAdj.begin()));

    std::set<Vertex> DintersectAdj;
    std::set_intersection(D.begin(), D.end(),
        Adj.begin(), Adj.end(),
        std::inserter(DintersectAdj, DintersectAdj.begin()));

    clique(NintersectAdj, DintersectAdj);

    S.erase(vertex);
    D.insert(vertex);
}
