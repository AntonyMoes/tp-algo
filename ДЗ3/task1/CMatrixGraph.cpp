//
// Created by antonymo on 18.12.18.
//

#include <set>
#include "CMatrixGraph.h"

void CMatrixGraph::AddEdge(int from, int to) {
    if (edges.size() <= from) {
        edges.resize(from + 1);
    }

    if (edges[from].size() <= to) {
        edges[from].resize(to + 1);
    }


    edges[from][to]++;
}

int CMatrixGraph::VerticesCount() const {
    std::set<int> vertices;

    for (int i = 0; i < edges.size(); ++i) {
        for (int j = 0; j < edges[i].size(); ++j) {
            if (edges[i][j] != 0) {
                vertices.insert(i);
                vertices.insert(j);
            }
        }
    }

    return vertices.size();
}

std::vector<int> CMatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> next_vertices;

    for (int i = 0; i < edges[vertex].size(); i++) {
        if (edges[vertex][i] > 0) {
            next_vertices.push_back(i);
        }
    }

    return next_vertices;
}

std::vector<int> CMatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev_vertices;

    for (int i = 0; i < edges.size(); i++) {
        if (edges[i][vertex] > 0) {
            prev_vertices.push_back(i);
        }
    }

    return prev_vertices;
}
