/*
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
#include "hash/xMap.h"

template<class T>
class TopoSorter {
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    int (*hash_code)(T&, int);
    
public:
    TopoSorter(DGraphModel<T>* graph, int (*hash_code)(T&, int)=0){
        this->graph = graph;
        this->hash_code = hash_code;
    }   
    DLinkedList<T> sort(int mode=0, bool sorted=true){
        if(mode == DFS) return dfsSort(sorted);
        else return bfsSort(sorted);
    }

    DLinkedList<T> bfsSort(bool sorted = true) { 
        DLinkedListSE<T> zero_list = listOfZeroInDegrees();
        if (sorted) zero_list.sort();
        Queue<T> list_bfs;           
        DLinkedList<T> list_topo_bfs;
        xMap<T, int> in_degree = vertex2inDegree(hash_code);
        for (auto it = zero_list.begin(); it != zero_list.end(); ++it) {
            list_bfs.push(*it);
        }
        while (!list_bfs.empty()){
            T vertex = list_bfs.pop();       
            list_topo_bfs.add(list_topo_bfs.size(), vertex);
            DLinkedList<T> outward_edges = graph -> getOutwardEdges(vertex);
            for (auto it = outward_edges.begin(); it != outward_edges.end(); ++it) {
                T visit = *it;
                int degree = in_degree.get(visit) - 1;
                in_degree.put(visit, degree);
                if (degree == 0){
                    list_bfs.push(visit);
                }
            }
        }
        return list_topo_bfs;
    }


    DLinkedList<T> dfsSort(bool sorted=true){
        DLinkedListSE<T> dfs = graph -> vertices();
        if(sorted) dfs.sort();
        Stack<T> list_dfs;
        DLinkedList<T> list_topo_dfs;
        xMap<T, bool> visited(hash_code);
        for (auto it = dfs.begin(); it != dfs.end(); ++it){
            visited.put(*it, false);
        }       
        for (auto it = dfs.begin(); it != dfs.end(); ++it){
            if (!visited.get(*it)){
                dfs_visit(*it, visited, list_topo_dfs);
            }
        }
        return list_topo_dfs; 
    }
protected:
    void dfs_visit(T vertex, xMap<T, bool>& visited, DLinkedList<T>& list_topo_dfs){
        visited.put(vertex, true);
        DLinkedList<T> outward_list = graph -> getOutwardEdges(vertex);
        for (auto it = outward_list.begin(); it != outward_list.end(); ++it) {
            T visit = *it;
            if (!visited.get(visit)){
                dfs_visit(visit, visited, list_topo_dfs);
            }
        }
        list_topo_dfs.add(0, vertex);
    }
    
    xMap<T, int> vertex2inDegree(int (*hash)(T&, int)) {
        xMap<T, int> in_degree(hash);
        DLinkedList<T> node = graph->vertices();
        typename DLinkedList<T>::Iterator it = node.begin();
        while (it != node.end()) {
            in_degree.put(*it, 0);
            ++it;
        }
        it = node.begin();
        while (it != node.end()) {
            DLinkedList<T> outward_list = graph -> getOutwardEdges(*it);
            typename DLinkedList<T>::Iterator in_it = outward_list.begin();
            while (in_it != outward_list.end()) {
                T visit = *in_it;
                int degree = in_degree.get(visit);
                in_degree.put(visit, degree + 1);
                ++in_it;
            }
            ++it;
        }
        return in_degree;
    }

    DLinkedList<T> listOfZeroInDegrees() {
        DLinkedList<T> zero_list;
        xMap<T, int> in_degree = vertex2inDegree(hash_code);
        DLinkedList<T> node = graph -> vertices();
        typename DLinkedList<T>::Iterator it = node.begin();
        while (it != node.end()){
            if (in_degree.get(*it) == 0){
                zero_list.add(zero_list.size(), *it);
            }
            ++it;
        }
        return zero_list;
    }
};

template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

#endif /* TOPOSORTER_H */
