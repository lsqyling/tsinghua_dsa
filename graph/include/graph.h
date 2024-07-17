//
// Created by shiqing on 2020/5/30.
//

#ifndef TSINGHUA_DATASTRUCTURE_GRAPH_H
#define TSINGHUA_DATASTRUCTURE_GRAPH_H

#include "../../part_1_linear/include/stack_queue.h"

namespace graph {
constexpr int INF = 0x3fff'ffff;
enum class VStatus
{
    UNDISCOVERED, DISCOVERED, VISITED
};

enum class EType
{
    UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD
};


template<typename Tv, typename Te>
class Graph
{
public:
    Graph() : n_(0), e_(0)
    {
    }

    virtual int insert(const Tv &) = 0;

    virtual Tv remove(int) = 0;

    virtual Tv &vertex(int) = 0;

    virtual int inDegree(int) = 0;

    virtual int outDegree(int) = 0;

    virtual int firstNeighbour(int) = 0;

    virtual int nextNeighbour(int, int) = 0;

    virtual VStatus &status(int) = 0;

    virtual int &dTime(int) = 0;

    virtual int &fTime(int) = 0;

    virtual int &parent(int) = 0;

    virtual int &priority(int) = 0;


    virtual bool exists(int, int) = 0;

    virtual void insert(const Te &, int, int, int) = 0;

    virtual Te remove(int, int) = 0;

    virtual EType &type(int, int) = 0;

    virtual Te &edge(int, int) = 0;

    virtual int &weight(int, int) = 0;

    void bfs(int);

    void dfs(int);

    void bcc(int);

    linear::stack<Tv> *tsort(int);

    void prim(int);

    void dijkstra(int);

    template<typename PU>
    void pfs(int, PU);

protected:
    int n_, e_;

private:
    void reset();

    void bfs(int s, int &clock);

    void dfs(int s, int &clock);

    void bbc(int, int &, linear::stack<int> &);

    void tsort(int, int &, linear::stack<Tv> *);
};

template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s)
{
    reset();
    int clock = 0, v = s;
    do
    {
        if (status(v) == VStatus::UNDISCOVERED)
        {
            bfs(v, clock);
        }
    } while (s != (v = ++v % n_));

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s)
{
    reset();
    int clock = 0, v = s;
    do
    {
        if (status(v) == VStatus::UNDISCOVERED)
        {
            dfs(v, clock);
        }
    } while (s != (v = ++v % n_));


}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int)
{

}

template<typename Tv, typename Te>
linear::stack<Tv> *Graph<Tv, Te>::tsort(int)
{
    return nullptr;
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::prim(int s)
{
    reset();
    priority(s) = 0;
    for (int i = 0; i < n_; ++i)
    {
        status(s) = VStatus::VISITED;
        if (parent(s) != -1) type(parent(s), s) = EType::TREE;
        for (int j = firstNeighbour(s); -1 < j; j = nextNeighbour(s, j))
        {
            if (status(j) == VStatus::UNDISCOVERED && priority(j) > weight(s, j))
            {
                priority(j) = weight(s, j);
                parent(j) = s;
            }
        }
        for (int shortest = INF, j = 0; j < n_; ++j)
        {
            if (status(j) == VStatus::UNDISCOVERED && priority(j) < shortest)
            {
                shortest = priority(j);
                s = j;
            }
        }
    }
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int s)
{
    reset();
    priority(s) = 0;
    for (int i = 0; i < n_; ++i)
    {
        status(s) = VStatus::VISITED;
        if (parent(s) != -1) type(parent(s), s) = EType::TREE;
        for (int j = firstNeighbour(s); -1 < j; j = nextNeighbour(s, j))
        {
            if (status(j) == VStatus::UNDISCOVERED && priority(j) > priority(s) + weight(s, j))
            {
                priority(j) = priority(s) + weight(s, j);
                parent(j) = s;
            }
        }
        for (int shortest = INF, j = 0; j < n_; ++j)
        {
            if (status(j) == VStatus::UNDISCOVERED && priority(j) < shortest)
            {
                shortest = priority(j);
                s = j;
            }
        }
    }
}

template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::pfs(int, PU)
{

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::reset()
{
    for (int i = 0; i < n_; ++i)
    {
        status(i) = VStatus::UNDISCOVERED;
        dTime(i) = fTime(i) = -1;
        parent(i) = -1;
        priority(i) = INF;
        for (int j = 0; j < n_; ++j)
        {
            if (exists(i, j)) type(i, j) = EType::UNDETERMINED;
        }
    }
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s, int &clock)
{
    linear::queue<int> Q;
    status(s) = VStatus::DISCOVERED;
    Q.enqueue(s);
    while (!Q.empty())
    {
        auto v = Q.dequeue();
        dTime(v) = ++clock;
        for (int u = firstNeighbour(v); -1 < u; u = nextNeighbour(v, u))
        {
            if (status(u) == VStatus::UNDISCOVERED)
            {
                status(u) = VStatus::DISCOVERED;
                Q.enqueue(u);
                type(v, u) = EType::TREE;
                parent(u) = v;
            }
            else
            {
                type(v, u) = EType::CROSS;
            }
        }
        status(v) = VStatus::VISITED;
    }
}


template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int v, int &clock)
{
    dTime(v) = ++clock;
    status(v) = VStatus::DISCOVERED;
    for (int u = firstNeighbour(v); -1 < u; u = nextNeighbour(v, u))
    {
        switch (status(u))
        {
            case VStatus::UNDISCOVERED:
                type(v, u) = EType::TREE;
                parent(u) = v;
                dfs(u, clock);
                break;
            case VStatus::DISCOVERED:
                type(v, u) = EType::BACKWARD;
                break;
            default:
                type(v, u) = dTime(v) < dTime(u) ? EType::FORWARD : EType::CROSS;
                break;
        }
    }
    status(v) = VStatus::VISITED;
    fTime(v) = ++clock;
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bbc(int, int &, linear::stack<int> &)
{

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::tsort(int, int &, linear::stack<Tv> *)
{

}

}


#endif //TSINGHUA_DATASTRUCTURE_GRAPH_H
