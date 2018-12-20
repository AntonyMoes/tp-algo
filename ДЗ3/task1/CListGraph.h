#ifndef TASK1_CLISTGRAPH_H
#define TASK1_CLISTGRAPH_H


#include <list>
#include <cstddef>
#include "IGraph.h"

class CListGraph : public IGraph {
  public:
    explicit CListGraph(IGraph* graph);
    explicit CListGraph(size_t size);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

  private:
    std::vector<std::list<int>> edges;
    const size_t size;
};


#endif  // TASK1_CLISTGRAPH_H
