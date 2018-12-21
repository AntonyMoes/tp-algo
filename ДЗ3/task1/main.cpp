#include <iostream>
#include "CListGraph.h"
#include "CMatrixGraph.h"
#include "CSetGraph.h"
#include "CArcGraph.h"
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;

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

#include <gtest/gtest.h>
#include <functional>

void BFS(const IGraph* graph, int vertex, std::function<void(int)> visit) {
    vector<bool> isQueued(graph->VerticesCount());
    queue<int> greyVertices;
    isQueued[vertex] = true;
    greyVertices.push(vertex);
    while (!greyVertices.empty()) {
        int currentVertex = greyVertices.front();
        visit(currentVertex);
        greyVertices.pop();
        vector<int> outVertices = graph->GetNextVertices(currentVertex);
        for (int i = 0; i < outVertices.size(); ++i) {
            if (!isQueued[outVertices[i]]) {
                isQueued[outVertices[i]] = true;
                greyVertices.push(outVertices[i]);
            }
        }
    }
}

void IGraphTestAddGetNext(IGraph* graph) {
    graph->AddEdge(0, 1);
    graph->AddEdge(0, 3);
    graph->AddEdge(1, 3);
    vector<int> tmp_vector;

    tmp_vector = graph->GetNextVertices(0);
    unordered_set<int> expected_out{1, 3};
    unordered_set<int> actual_out(tmp_vector.begin(), tmp_vector.end());
    ASSERT_EQ(expected_out, actual_out);
}

void IGraphTestAddGetPrev(IGraph* graph) {
    graph->AddEdge(0, 1);
    graph->AddEdge(0, 3);
    graph->AddEdge(1, 3);
    vector<int> tmp_vector;

    tmp_vector = graph->GetPrevVertices(3);
    unordered_set<int> expected_in{0, 1};
    unordered_set<int> actual_in(tmp_vector.begin(), tmp_vector.end());
    ASSERT_EQ(expected_in, actual_in);
}

void test_visit(int vertex,
                std::unordered_set<int>& first_layer,
                std::unordered_set<int>& second_layer,
                std::unordered_set<int>& third_layer) {
    if (first_layer.size() < 1) {
        first_layer.insert(vertex);
    } else if (second_layer.size() < 3) {
        second_layer.insert(vertex);
    } else {
        third_layer.insert(vertex);
    }
}

void IGraphTestBFS(IGraph* graph) {
    graph->AddEdge(1, 2);
    graph->AddEdge(1, 3);
    graph->AddEdge(1, 4);
    graph->AddEdge(2, 5);
    graph->AddEdge(3, 6);
    graph->AddEdge(3, 7);
    graph->AddEdge(3, 8);

    std::unordered_set<int> expected_first{1};
    std::unordered_set<int> expected_second{2, 3, 4};
    std::unordered_set<int> expected_third{5, 6, 7, 8};

    std::unordered_set<int> actual_first;
    std::unordered_set<int> actual_second;
    std::unordered_set<int> actual_third;

    BFS(graph, 1, std::bind(test_visit,
                            std::placeholders::_1,
                            std::ref(actual_first),
                            std::ref(actual_second),
                            std::ref(actual_third)));

    ASSERT_EQ(expected_first, actual_first);
    ASSERT_EQ(expected_second, actual_second);
    ASSERT_EQ(expected_third, actual_third);
}

TEST(CListGraphTest, AddGetNextTest) {
    CListGraph graph(5);
    IGraphTestAddGetNext(&graph);
}

TEST(CListGraphTest, AddGetPrevTest) {
    CListGraph graph(5);
    IGraphTestAddGetPrev(&graph);
}

TEST(CListGraphTest, BFSTest) {
    CListGraph graph(9);
    IGraphTestBFS(&graph);
}

TEST(CMatrixGraphTest, AddGetNextTest) {
    CMatrixGraph graph(5);
    IGraphTestAddGetNext(&graph);
}

TEST(CMatrixGraphTest, AddGetPrevTest) {
    CMatrixGraph graph(5);
    IGraphTestAddGetPrev(&graph);
}

TEST(CMatrixGraphTest, BFSTest) {
    CMatrixGraph graph(9);
    IGraphTestBFS(&graph);
}

TEST(CArcGraphTest, AddGetNextTest) {
    CArcGraph graph(5);
    IGraphTestAddGetNext(&graph);
}

TEST(CArcGraphTest, AddGetPrevTest) {
    CArcGraph graph(5);
    IGraphTestAddGetPrev(&graph);
}

TEST(CArcGraphTest, BFSTest) {
    CArcGraph graph(9);
    IGraphTestBFS(&graph);
}

TEST(CSetGraphTest, AddGetNextTest) {
    CSetGraph graph(5);
    IGraphTestAddGetNext(&graph);
}

TEST(CSetGraphTest, AddGetPrevTest) {
    CSetGraph graph(5);
    IGraphTestAddGetPrev(&graph);
}

TEST(CSetGraphTest, BFSTest) {
    CSetGraph graph(9);
    IGraphTestBFS(&graph);
}

template<typename Graph, typename TestGraph>
void CopyConstructTest() {
    Graph graph(9);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 4);
    graph.AddEdge(2, 5);
    graph.AddEdge(3, 6);
    graph.AddEdge(3, 7);
    graph.AddEdge(3, 8);

    TestGraph test_graph(&graph);

    vector<int> expected_tmp;
    vector<int> actual_tmp;
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        expected_tmp = graph.GetNextVertices(i);
        actual_tmp = test_graph.GetNextVertices(i);
        ASSERT_EQ(std::unordered_set<int>(expected_tmp.begin(), expected_tmp.end()),
                  std::unordered_set<int>(actual_tmp.begin(), actual_tmp.end())
        ) << "next " << i;

        expected_tmp = graph.GetPrevVertices(i);
        actual_tmp = test_graph.GetPrevVertices(i);
        ASSERT_EQ(expected_tmp, actual_tmp) << "prev " << i;
    }
}


TEST(CListGraph, CopyConstructListTest) {
    CopyConstructTest<CListGraph, CListGraph>();
}

TEST(CListGraph, CopyConstructMatrixTest) {
    CopyConstructTest<CListGraph, CMatrixGraph>();
}

TEST(CListGraph, CopyConstructArcTest) {
    CopyConstructTest<CListGraph, CArcGraph>();
}

TEST(CListGraph, CopyConstructSetTest) {
    CopyConstructTest<CListGraph, CSetGraph>();
}


TEST(CMatrixGraph, CopyConstructListTest) {
    CopyConstructTest<CMatrixGraph, CListGraph>();
}

TEST(CMatrixGraph, CopyConstructMatrixTest) {
    CopyConstructTest<CMatrixGraph, CMatrixGraph>();
}

TEST(CMatrixGraph, CopyConstructArcTest) {
    CopyConstructTest<CMatrixGraph, CArcGraph>();
}

TEST(CMatrixGraph, CopyConstructSetTest) {
    CopyConstructTest<CMatrixGraph, CSetGraph>();
}


TEST(CArcGraph, CopyConstructListTest) {
    CopyConstructTest<CArcGraph, CListGraph>();
}

TEST(CArcGraph, CopyConstructMatrixTest) {
    CopyConstructTest<CArcGraph, CMatrixGraph>();
}

TEST(CArcGraph, CopyConstructArcTest) {
    CopyConstructTest<CArcGraph, CArcGraph>();
}

TEST(CArcGraph, CopyConstructSetTest) {
    CopyConstructTest<CArcGraph, CSetGraph>();
}


TEST(CSetGraph, CopyConstructListTest) {
    CopyConstructTest<CSetGraph, CListGraph>();
}

TEST(CSetGraph, CopyConstructMatrixTest) {
    CopyConstructTest<CSetGraph, CMatrixGraph>();
}

TEST(CSetGraph, CopyConstructArcTest) {
    CopyConstructTest<CSetGraph, CArcGraph>();
}

TEST(CSetGraph, CopyConstructSetTest) {
    CopyConstructTest<CSetGraph, CSetGraph>();
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
