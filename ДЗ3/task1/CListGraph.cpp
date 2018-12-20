#include "CListGraph.h"
#include <algorithm>
#include <set>

void CListGraph::AddEdge(int from, int to) {
    if (edges.find(from) == edges.end()) {
        edges.emplace(from, std::list<int>());
    }

    edges[from].push_back(to);
}

int CListGraph::VerticesCount() const {
    std::set<int> vertices;

    for (const auto& item: edges) {
        vertices.insert(item.first);
        for (const auto verticle: item.second) {
            vertices.insert(verticle);
        }
    }

    return vertices.size();
}

std::vector<int> CListGraph::GetNextVertices(int vertex) const {
    std::vector<int> next_vertices;

    if (edges.find(vertex) != edges.end()) {
        for (auto next_vertex : edges.at(vertex)) {
            next_vertices.push_back(next_vertex);
        }
    }

    return next_vertices;
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev_vertices;

    for (const auto &item : edges) {
        if (std::find(item.second.begin(), item.second.end(), vertex) != item.second.end()) {
            prev_vertices.push_back(item.first);
        }
    }

    return prev_vertices;
}
