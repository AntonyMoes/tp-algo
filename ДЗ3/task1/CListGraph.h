#ifndef TASK1_CLISTGRAPH_H
#define TASK1_CLISTGRAPH_H


#include <list>
#include <map>
#include "IGraph.h"

class CListGraph : public IGraph {
public:
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

  private:
    std::map<int, std::list<int>> edges;
    int verticles_count = 0;
};


#endif  // TASK1_CLISTGRAPH_H
