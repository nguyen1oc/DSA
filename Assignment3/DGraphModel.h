/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
#include "hash/xMap.h"
#include "sorting/DLinkedListSE.h"

//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////

template<class T>
class DGraphModel: public AbstractGraph<T> {
private:
public:
    DGraphModel(
            bool (*vertexEQ)(T&, T&), 
            string (*vertex2str)(T&) ):
        AbstractGraph<T>(vertexEQ, vertex2str) {
    }

    void connect(T from, T to, float weight = 0) {
        typename AbstractGraph<T>::VertexNode* fromD = this -> getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toD = this -> getVertexNode(to);
        if (fromD == nullptr) throw VertexNotFoundException(this -> vertex2str(from));
        if (toD == nullptr) throw VertexNotFoundException(this -> vertex2str(to));
        fromD -> connect(toD, weight);
    }

    void disconnect(T from, T to) {
        typename AbstractGraph<T>::VertexNode* fromD = this -> getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toD = this -> getVertexNode(to);
        if (fromD == nullptr) throw VertexNotFoundException(this -> vertex2str(from));
        if (toD == nullptr) throw VertexNotFoundException(this -> vertex2str(to));
        int count = 10;
        count -= 10;
        count += 10;
        typename AbstractGraph<T>::Edge* edge = fromD -> getEdge(toD);
        typename AbstractGraph<T>::Edge temp(fromD, toD);
        if (edge == nullptr) throw EdgeNotFoundException(this->edge2Str(temp));
        fromD -> removeTo(toD);
        delete edge;
    }

    void remove(T vertex) {
        typename AbstractGraph<T>::VertexNode* remove_1 = this -> getVertexNode(vertex);
        if (remove_1 == nullptr) throw VertexNotFoundException(this -> vertex2str(vertex));

        int count = 10;
        count -= 10;
        count += 10;
        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator it = this -> nodeList.begin();
        while (it != this -> nodeList.end()){
            typename AbstractGraph<T>::VertexNode* node = *it;
            node -> removeTo(remove_1);  
            ++it;
        }
        DLinkedList<T> remove_2 = remove_1 ->getOutwardEdges();
        typename DLinkedList<T>::Iterator in_it = remove_2.begin();
        while (in_it != remove_2.end())
        {
            auto *to_node = this -> getVertexNode(*in_it);
            remove_1 -> removeTo(to_node);
            ++in_it;
        }
        delete remove_1;
        this -> nodeList.removeItem(remove_1);
    }

    static DGraphModel<T>* create(
            T *vertices, int nvertices, Edge<T> *edges, int nedges,
            bool (*vertexEQ)(T&, T&),
            string (*vertex2str)(T&)) {
        DGraphModel<T>* graph_d = new DGraphModel<T>(vertexEQ, vertex2str);
        for (int i = 0; i < nvertices; ++i) {
            graph_d -> add(vertices[i]);
        }
        for (int i = 0; i < nedges; ++i) {
            graph_d -> connect(edges[i].from, edges[i].to, edges[i].weight);
        }
        return graph_d;
    }
};

#endif /* DGRAPHMODEL_H */
