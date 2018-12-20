//
// Created by antonymo on 21.12.18.
//

#ifndef TASK1_CARCGRAPH_H_
#define TASK1_CARCGRAPH_H_


#include <cstddef>
#include "IGraph.h"

class CArcGraph : IGraph{
public:
    explicit CArcGraph(size_t size);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> edges;
    size_t size;

};


#endif  // TASK1_CARCGRAPH_H_
