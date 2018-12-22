#include <iostream>
#include <cstddef>
#include <vector>
#include <queue>
#include <list>
#include <cassert>
#include <algorithm>

class CListGraph {
public:
    explicit CListGraph(size_t size);

    void AddEdge(int from, int to);

    int VerticesCount() const;

    const std::vector<int>& GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;

private:
    std::vector<std::list<int>> edges;
    const size_t size;
};

void CListGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < size);
    assert(to >= 0 && to < size);

    edges[from].push_back(to);
    edges[to].push_back(from);
}

int CListGraph::VerticesCount() const {
    return size;
}

const std::vector<int>& CListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < size);
    static std::vector<int> next_vertices;
    next_vertices.clear();


    for (auto next_vertex : edges[vertex]) {
        if (std::find(next_vertices.begin(), next_vertices.end(), next_vertex) == next_vertices.end()) {  // защита от кратных ребер
            next_vertices.push_back(next_vertex);
        }
    }


    return next_vertices;
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < size);
    std::vector<int> prev_vertices;

    for (size_t i = 0; i < size; i++) {
        if (std::find(edges[i].begin(), edges[i].end(), vertex) != edges[i].end()) {
            prev_vertices.push_back(i);
        }
    }

    return prev_vertices;
}

CListGraph::CListGraph(size_t size) : size(size) {
    edges.resize(size);
}

CListGraph get_graph() {
    size_t vertices = 0;
    std::cin >> vertices;
    CListGraph graph(vertices);

    size_t edges = 0;
    std::cin >> edges;

    for (size_t i = 0; i < edges; ++i) {
        size_t from = 0;
        size_t to = 0;

        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }

    return graph;
}

struct Vertex {
    size_t path_count = 0;
    size_t depth = 0;
};

size_t get_ways(const CListGraph& graph, size_t start, size_t finish) {
    std::vector<Vertex> vertices(graph.VerticesCount());
    vertices[start].path_count = 1;

    std::queue<int> pending_vertices;
    pending_vertices.push(start);

    while (!pending_vertices.empty()) {
        int current_vertex = pending_vertices.front();
        pending_vertices.pop();
        auto next_vertices = graph.GetNextVertices(current_vertex);
        for (auto vertex : next_vertices) {
            if (vertices[vertex].path_count == 0) {
                vertices[vertex].path_count = vertices[current_vertex].path_count;
                vertices[vertex].depth = vertices[current_vertex].depth + 1;
                pending_vertices.push(vertex);
            } else if (vertices[vertex].depth == vertices[current_vertex].depth + 1) {
                vertices[vertex].path_count += vertices[current_vertex].path_count;
            }
        }
    }

    return vertices[finish].path_count;
}

int main() {
    auto graph = get_graph();

    size_t start = 0;
    size_t finish = 0;
    std::cin >> start >> finish;

    std::cout << get_ways(graph, start, finish);

    return 0;
}