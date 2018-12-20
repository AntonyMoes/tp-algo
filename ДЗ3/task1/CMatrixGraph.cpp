#include <cassert>
#include "CMatrixGraph.h"

void CMatrixGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < size);
    assert(to >= 0 && to < size);

    edges[from][to]++;
}

int CMatrixGraph::VerticesCount() const {
    return size;
}

std::vector<int> CMatrixGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < size);
    std::vector<int> next_vertices;

    for (int i = 0; i < edges[vertex].size(); i++) {
        if (edges[vertex][i] > 0) {
            next_vertices.push_back(i);
        }
    }

    return next_vertices;
}

std::vector<int> CMatrixGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < size);
    std::vector<int> prev_vertices;

    for (int i = 0; i < edges.size(); i++) {
        if (edges[i][vertex] > 0) {
            prev_vertices.push_back(i);
        }
    }

    return prev_vertices;
}

CMatrixGraph::CMatrixGraph(size_t size) : size(size) {
    edges.resize(size);
    for (auto &edge : edges) {
        edge.resize(size);
    }
}
