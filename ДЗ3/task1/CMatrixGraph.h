#ifndef TASK1_CMATRIXGRAPH_H
#define TASK1_CMATRIXGRAPH_H


#include <vector>
#include <cstddef>
#include "IGraph.h"

class CMatrixGraph : public IGraph {
public:
    explicit CMatrixGraph(size_t size);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> edges;
    size_t size;
};


#endif //TASK1_CMATRIXGRAPH_H
