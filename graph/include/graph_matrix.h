//
// Created by shiqing on 2020/5/30.
//

#ifndef TSINGHUA_DATASTRUCTURE_GRAPH_MATRIX_H
#define TSINGHUA_DATASTRUCTURE_GRAPH_MATRIX_H

#include "graph.h"
#include "../../part_1_linear/include/SVector.h"

namespace graph {
template<typename Tv>
struct Vertex
{
    explicit Vertex(const Tv &data = Tv())
            : data_(data), in_degree_(0), out_degree_(0), status_(VStatus::UNDISCOVERED),
              dtime_(-1), ftime_(-1), parent_(-1), priority_(INF)
    {
    }

    Tv data_;
    int in_degree_, out_degree_;
    VStatus status_;
    int dtime_, ftime_;
    int parent_, priority_;
};

template<typename Te>
struct Edge
{
    Edge(const Te &data, int w) : data_(data), weight_(w), type_(EType::UNDETERMINED)
    {
    }

    Te data_;
    int weight_;
    EType type_;
};

template<typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te>
{
public:
    ~GraphMatrix();

    int insert(const Tv &tv) override;

    Tv remove(int i) override;

    Tv &vertex(int i) override
    {
        return V_[i].data_;
    }

    int inDegree(int i) override
    {
        return V_[i].in_degree_;
    }

    int outDegree(int i) override
    {
        return V_[i].out_degree_;
    }

    int firstNeighbour(int i) override
    {
        return nextNeighbour(i, this->n_);
    }

    int nextNeighbour(int i, int j) override
    {
        while (-1 < j && !exists(i, --j)) return j;
    }

    VStatus &status(int i) override
    {
        return V_[i].status_;
    }

    int &dTime(int i) override
    {
        return V_[i].dtime_;
    }

    int &fTime(int i) override
    {
        return V_[i].ftime_;
    }

    int &parent(int i) override
    {
        return V_[i].parent_;
    }

    int &priority(int i) override
    {
        return V_[i].priority_;
    }

    bool exists(int i, int j) override
    {
        return 0 <= i && i < this->n_ && 0 <= j && j < this->n_ && E_[i][j] != nullptr;
    }

    void insert(const Te &, int w, int i, int j) override;

    Te remove(int, int) override;

    EType &type(int i, int j) override
    {
        return E_[i][j]->type_;
    }

    Te &edge(int i, int j) override
    {
        return E_[i][j]->data_;
    }

    int &weight(int i, int j) override
    {
        return E_[i][j]->weight_;
    }

private:
    linear::SVector<Vertex<Tv>> V_;
    linear::SVector<linear::SVector<Edge<Te> *>> E_;
};

template<typename Tv, typename Te>
GraphMatrix<Tv, Te>::~GraphMatrix()
{
    for (int i = 0; i < this->n_; ++i)
    {
        for (int j = 0; j < this->n_; ++j)
        {
            delete E_[i][j];
        }
    }
}

template<typename Tv, typename Te>
int GraphMatrix<Tv, Te>::insert(const Tv &tv)
{
    for (int j = 0; j < this->n_; ++j)
    {
        E_[j].insert(nullptr);
    }
    ++this->n_;
    E_.insert(SVector<Edge<Te> *>(this->n_, this->n_, nullptr));
    return V_.insert(Vertex<Tv>(tv));
}

template<typename Tv, typename Te>
Tv GraphMatrix<Tv, Te>::remove(int i)
{
    for (int j = 0; j < this->n_; ++j)
    {
        if (exists(i, j))
        {
            delete E_[i][j];
            --V_[j].in_degree_;
        }
    }
    E_.remove(i);
    --this->n_;
    Tv tmp = vertex(i);
    V_.remove(i);
    for (int j = 0; j < this->n_; ++j)
    {
        if (auto pe = E_[j].remove(i))
        {
            delete pe;
            --V_[j].out_degree_;
        }
    }
    return tmp;
}

template<typename Tv, typename Te>
void GraphMatrix<Tv, Te>::insert(const Te &e, int w, int i, int j)
{
    if (exists(i, j)) return;
    E_[i][j] = new Edge<Te>(e, w);
    ++this->e_;
    ++V_[i].out_degree_;
    ++V_[j].in_degree_;
}

template<typename Tv, typename Te>
Te GraphMatrix<Tv, Te>::remove(int i, int j)
{
    Te tmp = edge(i, j);
    delete E_[i][j];
    E_[i][j] = nullptr;
    --this->e_;
    V_[i].out_degree_;
    V_[j].in_degree_;
    return tmp;
}

}


#endif //TSINGHUA_DATASTRUCTURE_GRAPH_MATRIX_H
