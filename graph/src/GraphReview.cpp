//
// Created by shiqing on 19-8-6.
//
#include <cassert>
#include "../../part_1_linear/include/Stack.h"
#include "../../part_1_linear/include/Queue.h"
#include "../../common/CommonHeaders.h"

namespace graph {

using RefMGraph = struct AdjacencyMatrixNode &;
using PtrToMGraph = struct AdjacencyMatrixNode *;
using MGraph = struct AdjacencyMatrixNode;
using WeightType = int;
using VertexType = int;
using PtrToEdge = struct ENode *;

constexpr int Infinity = 0x80000000;
constexpr int MaxVertexNum = 256;

struct AdjacencyMatrixNode
{
    AdjacencyMatrixNode() : vNum_(0), eNum_(0)
    {
    }

    int vNum_;
    int eNum_;
    WeightType G[MaxVertexNum][MaxVertexNum]{};
};

struct ENode
{
    ENode() : v1_(-1), v2_(-1), weight_(Infinity)
    {
    }

    VertexType v1_, v2_;
    WeightType weight_;
};

PtrToMGraph createGraph(int vertexNum)
{
    assert(vertexNum <= MaxVertexNum);
    auto pG = new MGraph;
    pG->vNum_ = vertexNum;
    pG->eNum_ = 0;

    VertexType v, w;

    for (v = 0; v < pG->vNum_; ++v)
    {
        for (w = 0; w < pG->vNum_; ++w)
        {
            pG->G[v][w] = 0;
//                pG->G[v][w] = 0x80000000; Infinity
        }

    }
    return pG;
}

void insertEdge(PtrToMGraph pMGraph, PtrToEdge pEdge)
{
    if (pMGraph && pEdge)
    {
        pMGraph->G[pEdge->v1_][pEdge->v2_] = pEdge->weight_;
        pMGraph->G[pEdge->v2_][pEdge->v1_] = pEdge->weight_;
    }
}

/*
 * input sample:
 * Nv Ne
 * v1 v2 Weight
 * v3 v4 Weight
 * ....
 */

PtrToMGraph buildGraph()
{
    PtrToMGraph pG;
    PtrToEdge pe;
    VertexType v;
    int nv, i;

    scanf("%d", &nv);
    pG = createGraph(nv);
    scanf("%d", &pG->eNum_);

    if (pG->eNum_)
    {
        pe = new ENode;
        for (int j = 0; j < pG->eNum_; ++j)
        {
            scanf("%d %d %d", &pe->v1_, &pe->v2_, &pe->weight_);
            insertEdge(pG, pe);
        }
    }


    /*
     * if vertex has own data, read in.
     */
    /*for (v = 0; v < pG->vNum_; ++v) {
        scanf(" %c", &pG->data_[v]);
    }*/

    return pG;
}

using LGraph = struct GNode *;
using AdjList = struct VNode[MaxVertexNum];
using Edge = struct EdgeNode *;

struct EdgeNode
{
    int adjvex_;
    WeightType weight_;
    EdgeNode *next_;
};

struct VNode
{
    VertexType data_;
    EdgeNode *firstE_;
};

struct GNode
{
    GNode() : vNum_(0), eNum_(0)
    {
    }

    int vNum_;
    int eNum_;
    AdjList G;

};

LGraph createAdjListGraph(int vertexNum)
{
    LGraph graph;
    graph = new GNode;
    graph->vNum_ = vertexNum;
    graph->eNum_ = 0;

    VertexType v;
    for (v = 0; v < graph->vNum_; ++v)
    {
        graph->G[v].firstE_ = nullptr;
    }

    return graph;
}

void insertAdjListGraph(LGraph g, PtrToEdge e)
{
    if (g && e)
    {

        auto newENode = new EdgeNode;
        newENode->adjvex_ = e->v2_;
        newENode->weight_ = e->weight_;

        newENode->next_ = g->G[e->v1_].firstE_;
        g->G[e->v1_].firstE_ = newENode;
    }
}
}

namespace Page_206 {

constexpr int Infinity = 0x70000000;

struct EdgeNode
{
    int pointToVertexNo_ = -1;
    int weight_ = Infinity;
    EdgeNode *next_ = nullptr;
};

struct VertexNode
{
    EdgeNode *firstE_ = nullptr;
};

struct LGraph
{
    int vertexNum_ = 0;
    int verNoBegin_ = 0;
    VertexNode *EList = nullptr;
};

void initGraph(LGraph &G, int vertexNum, int vertexNoBegin = 0)
{
    assert(vertexNum > 0);
    G.vertexNum_ = vertexNum;
    G.verNoBegin_ = vertexNoBegin;
    G.EList = new VertexNode[vertexNum];
}

void insertEdge(LGraph &G, int vertexNo1, int vertexNo2)
{
    assert(G.verNoBegin_ <= vertexNo1 && vertexNo1 - G.verNoBegin_ < G.vertexNum_);
    assert(G.verNoBegin_ <= vertexNo2 && vertexNo2 - G.verNoBegin_ < G.vertexNum_);

    auto pe = new EdgeNode;
    pe->weight_ = 1;
    pe->pointToVertexNo_ = vertexNo2;
    pe->next_ = G.EList[vertexNo1 - G.verNoBegin_].firstE_;
    G.EList[vertexNo1 - G.verNoBegin_].firstE_ = pe;

    auto pe2 = new EdgeNode;
    pe2->weight_ = 1;
    pe2->pointToVertexNo_ = vertexNo1;
    pe2->next_ = G.EList[vertexNo2 - G.verNoBegin_].firstE_;
    G.EList[vertexNo2 - G.verNoBegin_].firstE_ = pe2;

}

void insertEdgeToDigraph(LGraph &G, int vertexNo1, int vertexNo2)
{
    assert(G.verNoBegin_ <= vertexNo1 && vertexNo1 - G.verNoBegin_ < G.vertexNum_);
    assert(G.verNoBegin_ <= vertexNo2 && vertexNo2 - G.verNoBegin_ < G.vertexNum_);

    auto pe = new EdgeNode;
    pe->weight_ = 1;
    pe->pointToVertexNo_ = vertexNo2;
    pe->next_ = G.EList[vertexNo1 - G.verNoBegin_].firstE_;
    G.EList[vertexNo1 - G.verNoBegin_].firstE_ = pe;
}

void destroyLGraph(LGraph &G)
{
    for (auto i = G.verNoBegin_; i < G.verNoBegin_ + G.vertexNum_; ++i)
    {
        for (auto p = G.EList[i - G.verNoBegin_].firstE_; p;)
        {
            auto tmp = p->next_;
            delete p;
            p = tmp;
        }
    }
    delete[] G.EList;
}

void DFS(LGraph &G, int &cntEdge, int vertexNo, bool visited[])
{
    visited[vertexNo - G.verNoBegin_] = true;
    for (EdgeNode *p = G.EList[vertexNo - G.verNoBegin_].firstE_; p; p = p->next_)
    {
        ++cntEdge;
        if (!visited[p->pointToVertexNo_ - G.verNoBegin_])
        {
            DFS(G, cntEdge, p->pointToVertexNo_, visited);
        }
    }
}

/*
 * Question 2: is the graph a tree?
 */
bool isTree(LGraph &G)
{
    bool *visited = new bool[G.vertexNum_]{0};
    for (int j = 0; j < G.vertexNum_; ++j)
    {
        visited[j] = false;
    }
    int vertexNo = 1, cntEdge = 0;
    DFS(G, cntEdge, vertexNo, visited);

    int cnt = 0;
    for (int i = 0; i < G.vertexNum_; ++i)
    {
        if (visited[i]) ++cnt;
    }

    delete[] visited;

    return cnt == G.vertexNum_ && cntEdge / 2 == G.vertexNum_ - 1;
}

void testingIsTree()
{
    LGraph G;
    initGraph(G, 5, 1);

    insertEdge(G, 1, 2);
    insertEdge(G, 1, 3);
    insertEdge(G, 1, 4);
    insertEdge(G, 2, 3);
    insertEdge(G, 2, 4);
    insertEdge(G, 2, 5);
    insertEdge(G, 3, 4);
    insertEdge(G, 4, 5);

    cout << isTree(G) << endl;
    destroyLGraph(G);

    LGraph g;
    initGraph(g, 5, 1);

    insertEdge(g, 1, 2);
    insertEdge(g, 1, 3);
    insertEdge(g, 1, 4);
    insertEdge(g, 2, 5);

    cout << isTree(g) << endl;
    destroyLGraph(g);

}

/*
 * Question 3: DFS that is no recursive implemented.
 */
void DFSNoneRecursive(LGraph &G, int vertexNo)
{
    bool *visited = new bool[G.vertexNum_]{0};
    linear::Stack<int> S;
    S.push(vertexNo);
    int wNo;
    visited[vertexNo - G.verNoBegin_] = true;
    while (!S.empty())
    {
        wNo = S.pop();
        cout << wNo << " ";
        for (auto p = G.EList[wNo - G.verNoBegin_].firstE_; p; p = p->next_)
        {
            if (!visited[p->pointToVertexNo_ - G.verNoBegin_])
            {
                S.push(p->pointToVertexNo_);
                visited[p->pointToVertexNo_ - G.verNoBegin_] = true;
            }
        }
    }

    delete[] visited;

}

void testingDFSNoneRecursive()
{
    LGraph G;
    initGraph(G, 5, 1);

    insertEdge(G, 1, 2);
    insertEdge(G, 1, 3);
    insertEdge(G, 1, 4);
    insertEdge(G, 2, 3);
    insertEdge(G, 2, 4);
    insertEdge(G, 2, 5);
    insertEdge(G, 3, 4);
    insertEdge(G, 4, 5);

    DFSNoneRecursive(G, 1);
    destroyLGraph(G);

    LGraph g;
    initGraph(g, 5, 1);

    insertEdge(g, 1, 2);
    insertEdge(g, 1, 3);
    insertEdge(g, 1, 4);
    insertEdge(g, 2, 5);

    cout << endl;
    DFSNoneRecursive(g, 1);
    destroyLGraph(g);
}

void dfsExisted(LGraph &G, int vertexNo1, int vertexNo2, bool visited[])
{
    visited[vertexNo1 - G.verNoBegin_] = true;
    if (vertexNo1 == vertexNo2) return;
    for (auto p = G.EList[vertexNo1 - G.verNoBegin_].firstE_; p; p = p->next_)
    {
        if (!visited[p->pointToVertexNo_ - G.verNoBegin_])
        {
            dfsExisted(G, p->pointToVertexNo_, vertexNo2, visited);
        }
    }
}

void bfsExisted(LGraph &G, int vertexNo1, int vertexNo2, bool visited[])
{
    linear::Queue<int> Q;
    Q.enqueue(vertexNo1);
    visited[vertexNo1 - G.verNoBegin_] = true;
    int wNo;
    while (!Q.empty())
    {
        wNo = Q.dequeue();
        for (auto p = G.EList[wNo - G.verNoBegin_].firstE_; p; p = p->next_)
        {
            if (!visited[p->pointToVertexNo_ - G.verNoBegin_])
            {
                visited[p->pointToVertexNo_ - G.verNoBegin_] = true;
                if (p->pointToVertexNo_ == vertexNo2) return;
                Q.enqueue(p->pointToVertexNo_);
            }
        }
    }
}

/*
 * Question 4: is digraph existed path A to B ?
 */
bool isExistedPathDFS(LGraph &G, int vertexNo1, int vertexNo2)
{
    bool *visited = new bool[G.verNoBegin_]{0};
    dfsExisted(G, vertexNo1, vertexNo2, visited);
    auto r = visited[vertexNo2 - G.verNoBegin_];
    delete[] visited;
    return r;
}

bool isExistedPathBFS(LGraph &G, int vertexNo1, int vertexNo2)
{
    bool *visited = new bool[G.verNoBegin_]{0};
    bfsExisted(G, vertexNo1, vertexNo2, visited);
    auto r = visited[vertexNo2 - G.verNoBegin_];
    delete[] visited;
    return r;
}

void testingIsExisted()
{
    LGraph G;
    initGraph(G, 6, 1);

    insertEdgeToDigraph(G, 1, 2);
    insertEdgeToDigraph(G, 1, 4);

    insertEdgeToDigraph(G, 2, 5);
    insertEdgeToDigraph(G, 3, 5);
    insertEdgeToDigraph(G, 3, 6);

    insertEdgeToDigraph(G, 4, 2);
    insertEdgeToDigraph(G, 5, 4);

    cout << isExistedPathDFS(G, 1, 5) << " ";
    cout << isExistedPathDFS(G, 2, 4) << " ";
    cout << isExistedPathDFS(G, 3, 2) << " ";
    cout << isExistedPathDFS(G, 3, 1) << " ";
    cout << isExistedPathDFS(G, 1, 6) << " ";
    cout << isExistedPathDFS(G, 5, 1) << endl;

    cout << isExistedPathBFS(G, 1, 5) << " ";
    cout << isExistedPathBFS(G, 2, 4) << " ";
    cout << isExistedPathBFS(G, 3, 2) << " ";
    cout << isExistedPathBFS(G, 3, 1) << " ";
    cout << isExistedPathBFS(G, 1, 6) << " ";
    cout << isExistedPathBFS(G, 5, 1) << endl;

    destroyLGraph(G);
}

void printArray(int *path, int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << path[i] << " ";
    }
    cout << endl;
}

/*
 * Question 5: print path from A to B;
 */
void printPathFromA2B(LGraph &G, int u, int v, int path[], bool visited[], int dist)
{
    path[++dist] = u;
    visited[u - G.verNoBegin_] = 1;
    if (u == v)
    {
        printArray(path, dist + 1);
    }

    int wNo;
    EdgeNode *p = G.EList[u - G.verNoBegin_].firstE_;
    while (p)
    {
        wNo = p->pointToVertexNo_;
        if (!visited[wNo - G.verNoBegin_])
        {
            printPathFromA2B(G, wNo, v, path, visited, dist);
        }
        p = p->next_;
    }
    visited[u - G.verNoBegin_] = 0;
}

void printPathFromA2BNoneRecursive(LGraph &G, int u, int v)
{
    bool *visited = new bool[G.vertexNum_]{0};
    int *path = new int[G.vertexNum_];

    linear::Stack<int> S;
    S.push(u);
    visited[u - G.verNoBegin_] = 1;
    int w, dist = -1;
    while (!S.empty())
    {
        w = S.pop();
        path[++dist] = w;
        if (w == v)
        {
            printArray(path, dist + 1);
        }
        for (auto p = G.EList[w - G.verNoBegin_].firstE_; p; p = p->next_)
        {
            if (!visited[p->pointToVertexNo_ - G.verNoBegin_])
            {
                S.push(p->pointToVertexNo_);
                visited[p->pointToVertexNo_ - G.verNoBegin_] = 1;
            }
        }
    }

    delete[] visited;
    delete[] path;
}

void testingPrintPathFromA2B()
{
    LGraph G;
    initGraph(G, 6, 1);

    insertEdgeToDigraph(G, 1, 2);
    insertEdgeToDigraph(G, 1, 4);

    insertEdgeToDigraph(G, 2, 5);
    insertEdgeToDigraph(G, 3, 5);
    insertEdgeToDigraph(G, 3, 6);

    insertEdgeToDigraph(G, 4, 2);
    insertEdgeToDigraph(G, 5, 4);

    bool *visited = new bool[G.vertexNum_]{0};
    int *path = new int[G.vertexNum_];
    for (int i = 0; i < G.vertexNum_; ++i)
    {
        path[i] = -1;
    }
    printf("%d ----> %d:\n", 1, 5);
    printPathFromA2B(G, 1, 5, path, visited, -1);
    printf("%d ----> %d:\n", 2, 4);
    printPathFromA2B(G, 2, 4, path, visited, -1);
    printf("%d ----> %d:\n", 3, 2);
    printPathFromA2B(G, 3, 2, path, visited, -1);
    printf("%d ----> %d:\n", 3, 1);
    printPathFromA2B(G, 3, 1, path, visited, -1);
    printf("%d ----> %d:\n", 1, 6);
    printPathFromA2B(G, 1, 6, path, visited, -1);
    printf("%d ----> %d:\n", 5, 1);
    printPathFromA2B(G, 5, 1, path, visited, -1);
    delete[] visited;
    delete[] path;

    cout << endl;
    printf("%d ----> %d:\n", 1, 5);
    printPathFromA2BNoneRecursive(G, 1, 5);
    printf("%d ----> %d:\n", 2, 4);
    printPathFromA2BNoneRecursive(G, 2, 4);
    printf("%d ----> %d:\n", 3, 2);
    printPathFromA2BNoneRecursive(G, 3, 2);
    printf("%d ----> %d:\n", 3, 1);
    printPathFromA2BNoneRecursive(G, 3, 1);
    printf("%d ----> %d:\n", 1, 6);
    printPathFromA2BNoneRecursive(G, 1, 6);
    printf("%d ----> %d:\n", 5, 1);
    printPathFromA2BNoneRecursive(G, 5, 1);
}

}

void TestingNamespacePage_206()
{
    Page_206::testingIsTree();
    Page_206::testingDFSNoneRecursive();
    Page_206::testingIsExisted();
    Page_206::testingPrintPathFromA2B();
}

int main(int argc, char *argv[])
{
    TestingNamespacePage_206();

    return 0;
}







