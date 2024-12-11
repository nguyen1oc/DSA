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
        if (fromU == nullptr) throw VertexNotFoundException(this->vertex2str(from));
        if (toU == nullptr) throw VertexNotFoundException(this->vertex2str(to));
        if (fromU != toU){
           typename AbstractGraph<T>::Edge* edge_2 = toU -> getEdge(fromU);
           if (edge_2 == nullptr) throw EdgeNotFoundException(this->edge2Str(*edge_2));
           toU -> removeTo(fromU);
        }
        typename AbstractGraph<T>::Edge* edge_1 = fromU -> getEdge(toU);
        if (edge_1 == nullptr) throw EdgeNotFoundException(this->edge2Str(*edge_1));
        fromU -> removeTo(toU);
    }
    void remove(T vertex)
    {
        typename AbstractGraph<T>::VertexNode* remove_1 = this -> getVertexNode(vertex);
        if (remove_1 == nullptr) throw VertexNotFoundException(this -> vertex2str(vertex));

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
        this -> nodeList.removeItem(remove_1);
        delete remove_1;
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
