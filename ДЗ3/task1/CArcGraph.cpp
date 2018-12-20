#include "CArcGraph.h"
#include <cassert>
#include <algorithm>

void CArcGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < size);
    assert(to >= 0 && to < size);

    edges.emplace_back(std::make_pair(from, to));
}

int CArcGraph::VerticesCount() const {
    return size;
}

std::vector<int> CArcGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < size);
    std::vector<int> next_vertices;


    for (const auto& pair : edges) {
        if (pair.first == vertex && std::find(next_vertices.begin(), next_vertices.end(), pair.second) == next_vertices.end()) {
            next_vertices.push_back(pair.second);
        }
    }


    return next_vertices;
}

std::vector<int> CArcGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < size);
    std::vector<int> prev_vertices;

    for (const auto& pair : edges) {
        if (pair.second == vertex && std::find(prev_vertices.begin(), prev_vertices.end(), pair.first) == prev_vertices.end()) {
            prev_vertices.push_back(pair.second);
        }
    }
    return prev_vertices;
}

CArcGraph::CArcGraph(size_t size) : size(size) {}

CArcGraph::CArcGraph(IGraph *graph) : CArcGraph(graph->VerticesCount()){
    for (size_t i = 0; i < size; ++i) {
        auto next_vertices = graph->GetNextVertices(i);
        for (auto vertex : next_vertices) {
            edges.emplace_back(std::make_pair(i, vertex));
        }
    }
}
