/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str)
    {
    }

    void connect(T from, T to, float weight = 0)
    {
        typename AbstractGraph<T>::VertexNode* fromU = this -> getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toU = this -> getVertexNode(to);
        if (fromU == nullptr) throw VertexNotFoundException(this -> vertex2str(from));
        if (toU == nullptr) throw VertexNotFoundException(this -> vertex2str(to));
        if (fromU != toU){
            toU -> connect(fromU, weight);
        }
            fromU -> connect(toU, weight);
    }
    void disconnect(T from, T to)
    {
        typename AbstractGraph<T>::VertexNode* fromU = this -> getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toU = this -> getVertexNode(to);
        if (fromU == nullptr) throw VertexNotFoundException(this -> vertex2str(from));
        if (toU == nullptr) throw VertexNotFoundException(this -> vertex2str(to));

        typename AbstractGraph<T>::Edge* edge_1 = fromU -> getEdge(toU);
        typename AbstractGraph<T>::Edge temp_1(fromU, toU);
        typename AbstractGraph<T>::Edge* edge_2 = toU -> getEdge(fromU);
        typename AbstractGraph<T>::Edge temp_2(toU, fromU);
        if (edge_1 == nullptr) throw EdgeNotFoundException(this -> edge2Str(temp_1));
        if (edge_2 == nullptr) throw EdgeNotFoundException(this -> edge2Str(temp_2));

        int count = 10;
        count -= 10;
        count += 10;
        if (fromU != toU){
            toU -> removeTo(fromU);
            delete edge_2;
        }
            fromU -> removeTo(toU);
            delete edge_1;
    }
    void remove(T vertex)
    {
        typename AbstractGraph<T>::VertexNode* remove_1 = this -> getVertexNode(vertex);
        if (remove_1 == nullptr) throw VertexNotFoundException(this -> vertex2str(vertex));
        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator it = this -> nodeList.begin();
        while (it != this -> nodeList.end()) {
            typename AbstractGraph<T>::VertexNode* remove_incre = *it;
            if (remove_incre != remove_1) {
                remove_incre -> removeTo(remove_1);
                remove_1 -> removeTo(remove_incre);
            }
            it++;
        }
        int count = 10;
        count -= 10;
        count += 10;
        delete remove_1;
        this -> nodeList.removeItem(remove_1);
    }
    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        UGraphModel<T>* graph_u = new UGraphModel<T>(vertexEQ, vertex2str);
        for (int i = 0; i < nvertices; i++) {
            graph_u -> add(vertices[i]);
        }
        for (int i = 0; i < nedges; i++) {
            graph_u -> connect(edges[i].from, edges[i].to, edges[i].weight);
        }
        return graph_u;
    }
};

#endif /* UGRAPHMODEL_H */
