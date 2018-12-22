#include <iostream>
#include <cstddef>
#include <vector>
#include <queue>
#include <list>
#include <cassert>
#include <algorithm>
#include <set>
#include <climits>

class CListGraph {
public:
    explicit CListGraph(size_t size);

    void AddEdge(int from, int to, int distance);

    int VerticesCount() const;

    const std::vector<std::pair<int, int>>& GetNextVertices(int vertex) const;

private:
    std::vector<std::list<std::pair<int, int>>> edges;
    const size_t size;
};

void CListGraph::AddEdge(int from, int to, int distance) {
    assert(from >= 0 && from < size);
    assert(to >= 0 && to < size);

    edges[from].emplace_back(std::make_pair(to, distance));
    edges[to].emplace_back(std::make_pair(from ,distance));
}

int CListGraph::VerticesCount() const {
    return size;
}

const std::vector<std::pair<int, int>>& CListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < size);
    static std::vector<std::pair<int, int>> next_vertices;
    next_vertices.clear();


    for (auto next_vertex : edges[vertex]) {
            next_vertices.push_back(next_vertex);
    }


    return next_vertices;
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
        size_t distance = 0;

        std::cin >> from >> to >> distance;
        graph.AddEdge(from, to, distance);
    }

    return graph;
}

size_t get_way(const CListGraph& graph, size_t start, size_t finish) {
    assert(start >= 0 && start < graph.VerticesCount());
    assert(finish >= 0 && finish < graph.VerticesCount());

    std::vector<int> depths(graph.VerticesCount(), INT_MAX);
    depths[start] = 0;
    std::priority_queue<std::pair<int,int>,
            std::vector<std::pair<int,int>>,
            std::greater<std::pair<int, int>>> vertices_queue;

    vertices_queue.push(std::make_pair(start, 0));
    while (!vertices_queue.empty()) {
        int from = vertices_queue.top().first;
        int weight = vertices_queue.top().second;
        vertices_queue.pop();
        // Скипаем фиктивные вершины
        if (weight <= depths[from]) {
            auto paths = graph.GetNextVertices(from);
            for (auto& path : paths) {
                int to = path.first;
                int length = path.second;
                if (depths[from] + length < depths[to]) {
                    depths[to] = depths[from] + length;
                    vertices_queue.push(std::make_pair(to, depths[to]));
                }
            }
        }
    }
    return depths[finish];
}

int main() {
    auto graph = get_graph();

    size_t start = 0;
    size_t finish = 0;
    std::cin >> start >> finish;

    std::cout << get_way(graph, start, finish);

    return 0;
}