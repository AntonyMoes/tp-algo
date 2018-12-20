#include "CListGraph.h"
#include <algorithm>
#include <set>
#include <cassert>

void CListGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < size);
    assert(to >= 0 && to < size);

    edges[from].push_back(to);
}

int CListGraph::VerticesCount() const {
    return size;
}

std::vector<int> CListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < size);
    std::vector<int> next_vertices;


    for (auto next_vertex : edges.at(vertex)) {
        if (std::find(next_vertices.begin(), next_vertices.end(), next_vertex) == next_vertices.end()) {
            next_vertices.push_back(next_vertex);
        }
    }


    return next_vertices;
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < size);
    std::vector<int> prev_vertices;

    for (const auto &item : edges) {
        if (std::find(item.second.begin(), item.second.end(), vertex) != item.second.end()) {
            prev_vertices.push_back(item.first);
        }
    }

    return prev_vertices;
}
