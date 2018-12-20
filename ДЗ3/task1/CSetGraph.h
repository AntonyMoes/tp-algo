#ifndef TASK1_CSETGRAPH_H_
#define TASK1_CSETGRAPH_H_


#include <cstddef>
#include <set>
#include "IGraph.h"

class CSetGraph : public IGraph {
public:
    explicit CSetGraph(size_t size);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::set<int>> edges;
    size_t size;

};


#endif  // TASK1_CSETGRAPH_H_
