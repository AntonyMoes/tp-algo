#ifndef TASK1_CMATRIXGRAPH_H
#define TASK1_CMATRIXGRAPH_H


#include <vector>
#include "IGraph.h"

class CMatrixGraph : public IGraph {
public:
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> edges;
};


#endif //TASK1_CMATRIXGRAPH_H
