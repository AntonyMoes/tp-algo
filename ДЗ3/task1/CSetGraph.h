#ifndef TASK1_CSETGRAPH_H_
#define TASK1_CSETGRAPH_H_


#include <cstddef>
#include <unordered_set>
#include "IGraph.h"

class CSetGraph : public IGraph {
public:
    explicit CSetGraph(IGraph* graph);
    explicit CSetGraph(size_t size);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::unordered_set<int>> edges;
    const size_t size;

};


#endif  // TASK1_CSETGRAPH_H_
