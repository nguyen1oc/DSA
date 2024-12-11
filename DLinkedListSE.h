/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class DLinkedListSE: public DLinkedList<T> {
public:
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ){
        
    };
    
    DLinkedListSE(const DLinkedList<T>& list){
        this->copyFrom(list);
    }
    
    void sort(int (*comparator)(T&,T&)=0){
        if(this->count <= 1) return;
        mergeSort(this-> head -> next, this -> tail -> prev, comparator);
    };
    
protected:
    void mergeSort(typename DLinkedList<T>::Node* start, typename DLinkedList<T>::Node* end, int (*comparator)(T&,T&)){
        if(start == nullptr || end == nullptr || start == end) return;
        typename DLinkedList<T>::Node* middle = findMiddle(start, end);
        typename DLinkedList<T>::Node* next_to = middle -> next;
        mergeSort(start, middle, comparator);
        mergeSort(next_to, end, comparator);
        mergeLists(start, middle, end, comparator);
    }
    
    typename DLinkedList<T>::Node* findMiddle(typename DLinkedList<T>::Node* start, typename DLinkedList<T>::Node* end){
        typename DLinkedList<T>::Node* slow = start;
        typename DLinkedList<T>::Node* fast = start;
        while(fast != end && fast -> next != end){
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        return slow;
    }
    
    void mergeLists(typename DLinkedList<T>::Node* start, typename DLinkedList<T>::Node* midpoint, typename DLinkedList<T>::Node* end, int (*comparator)(T&, T&)){
        typename DLinkedList<T>::Node* leftIterator = start;
        typename DLinkedList<T>::Node* rightIterator = midpoint->next;
        DLinkedList<T> mergedList;
        while (leftIterator != midpoint -> next && rightIterator != end->next){
            if (compare(leftIterator -> data, rightIterator -> data, comparator) <= 0){
                mergedList.add(mergedList.size(), leftIterator -> data);
                leftIterator = leftIterator -> next;
            } 
            else{
                mergedList.add(mergedList.size(), rightIterator->data);
                rightIterator = rightIterator->next;
            }
        }
        for (; leftIterator != midpoint -> next; leftIterator = leftIterator -> next){
            mergedList.add(mergedList.size(), leftIterator->data);
        }
        for (; rightIterator != end -> next; rightIterator = rightIterator -> next){
            mergedList.add(mergedList.size(), rightIterator->data);
        }
        typename DLinkedList<T>::Node* originalIterator = start;
        typename DLinkedList<T>::Iterator mergedIterator = mergedList.begin();
        while (mergedIterator != mergedList.end()){
            originalIterator->data = *mergedIterator;
            originalIterator = originalIterator->next;
            ++mergedIterator;
        }
    }

    int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return 1;
            else return 0;
        }
    }
};

#endif /* DLINKEDLISTSE_H */
