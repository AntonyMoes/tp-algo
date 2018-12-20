#ifndef TASK1_CLISTGRAPH_H
#define TASK1_CLISTGRAPH_H


#include <list>
#include <map>
#include "IGraph.h"

class CListGraph : public IGraph {
  public:
    explicit CListGraph(size_t size) : size(size) {
        for (size_t i = 0; i < size; ++i) {
            edges.emplace(i, std::list<int>());
        }
    }

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

  private:
    std::map<int, std::list<int>> edges;
    size_t size;
};


#endif  // TASK1_CLISTGRAPH_H
