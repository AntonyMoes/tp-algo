#include <iostream>
#include "CListGraph.h"
#include "CMatrixGraph.h"
#include "CSetGraph.h"
#include "CArcGraph.h"
#include <algorithm>

void show_graph(const IGraph* graph) {
    int n = graph->VerticesCount();

    for (size_t i = 0; i < n; ++i) {
        auto vertices = graph->GetNextVertices(i);
        for (size_t j = 0; j < n; ++j) {
            if (std::find(vertices.begin(), vertices.end(), j) != vertices.end()) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

int main() {
    CListGraph graph1(4);
    graph1.AddEdge(0, 1);
    graph1.AddEdge(1, 2);
    graph1.AddEdge(2, 3);
    graph1.AddEdge(3, 0);

    CMatrixGraph graph2(&graph1);
    CSetGraph graph3(&graph2);
    CArcGraph graph4(&graph3);

    show_graph(&graph1);
    show_graph(&graph2);
    show_graph(&graph3);
    show_graph(&graph4);

    return 0;
}