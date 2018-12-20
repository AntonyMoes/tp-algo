#include "CSetGraph.h"
#include <cassert>

void CSetGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < size);
    assert(to >= 0 && to < size);

    edges[from].insert(to);
}

int CSetGraph::VerticesCount() const {
    return size;
}

std::vector<int> CSetGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < size);
    std::vector<int> next_vertices;

    for (auto next_vertex : edges[vertex]) {
        next_vertices.push_back(next_vertex);
    }

    return next_vertices;
}

std::vector<int> CSetGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < size);
    std::vector<int> prev_vertices;

    for (size_t i = 0; i < size; i++) {
        if (edges[i].find(vertex) != edges[i].end()) {
            prev_vertices.push_back(i);
        }
    }

    return prev_vertices;
}

CSetGraph::CSetGraph(size_t size) : size(size) {
    edges.resize(size);
}

CSetGraph::CSetGraph(IGraph *graph) : CSetGraph(graph->VerticesCount()){
    for (size_t i = 0; i < size; ++i) {
        auto next_vertices = graph->GetNextVertices(i);
        for (auto vertex : next_vertices) {
            edges[i].insert(vertex);
        }
    }
}
