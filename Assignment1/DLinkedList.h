/*
 * File:   DLinkedList.h
 */

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "list/IList.h"

#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class DLinkedList : public IList<T>
{
public:
    class Node;        // Forward declaration
    class Iterator;    // Forward declaration
    class BWDIterator; // Forward declaration

protected:
    Node *head; // this node does not contain user's data
    Node *tail; // this node does not contain user's data
    int count;
    bool (*itemEqual)(T &lhs, T &rhs);        // function pointer: test if two items (type: T&) are equal or not
    void (*deleteUserData)(DLinkedList<T> *); // function pointer: be called to remove items (if they are pointer type)

public:
    DLinkedList(
        void (*deleteUserData)(DLinkedList<T> *) = 0,
        bool (*itemEqual)(T &, T &) = 0);
    DLinkedList(const DLinkedList<T> &list);
    DLinkedList<T> &operator=(const DLinkedList<T> &list);
    ~DLinkedList();

    // Inherit from IList: BEGIN
    void add(T e);
    void add(int index, T e);
    T removeAt(int index);
    bool removeItem(T item, void (*removeItemData)(T) = 0);
    bool empty();
    int size();
    void clear();
    T &get(int index);
    int indexOf(T item);
    void checkIndex(int index);
    void checkRealIndex(int index);
    bool contains(T item);
    string toString(string (*item2str)(T &) = 0);
    // Inherit from IList: END

    void println(string (*item2str)(T &) = 0)
    {
        cout << toString(item2str) << endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(DLinkedList<T> *) = 0)
    {
        this->deleteUserData = deleteUserData;
    }

    bool contains(T array[], int size)
    {
        int idx = 0;
        for (DLinkedList<T>::Iterator it = begin(); it != end(); it++)
        {
            if (!equals(*it, array[idx++], this->itemEqual))
                return false;
        }
        return true;
    }

    /*
     * free(DLinkedList<T> *list):
     *  + to remove user's data (type T, must be a pointer type, e.g.: int*, Point*)
     *  + if users want a DLinkedList removing their data,
     *      he/she must pass "free" to constructor of DLinkedList
     *      Example:
     *      DLinkedList<T> list(&DLinkedList<T>::free);
     */
    static void free(DLinkedList<T> *list)
    {
        typename DLinkedList<T>::Iterator it = list->begin();
        while (it != list->end())
        {
            delete *it;
            it++;
        }
    }

    /* begin, end and Iterator helps user to traverse a list forwardly
     * Example: assume "list" is object of DLinkedList

     DLinkedList<char>::Iterator it;
     for(it = list.begin(); it != list.end(); it++){
            char item = *it;
            std::cout << item; //print the item
     }
     */
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }

    /* last, beforeFirst and BWDIterator helps user to traverse a list backwardly
     * Example: assume "list" is object of DLinkedList

     DLinkedList<char>::BWDIterator it;
     for(it = list.last(); it != list.beforeFirst(); it--){
            char item = *it;
            std::cout << item; //print the item
     }
     */
    BWDIterator bbegin()
    {
        return BWDIterator(this, true);
    }
    BWDIterator bend()
    {
        return BWDIterator(this, false);
    }

protected:
    static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &))
    {
        if (itemEqual == 0)
            return lhs == rhs;
        else
            return itemEqual(lhs, rhs);
    }
    void copyFrom(const DLinkedList<T> &list);
    void removeInternalData();
    Node *getPreviousNodeOf(int index);

    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
public:
    class Node
    {
    public:
        T data;
        Node *next;
        Node *prev;
        friend class DLinkedList<T>;

    public:
        Node(Node *next = 0, Node *prev = 0)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next = 0, Node *prev = 0)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    //////////////////////////////////////////////////////////////////////
    class Iterator
    {
    private:
        DLinkedList<T> *pList;
        Node *pNode;

    public:
        Iterator(DLinkedList<T> *pList = 0, bool begin = true)
        {
            if (begin)
            {
                if (pList != 0)
                    this->pNode = pList->head->next;
                else
                    pNode = 0;
            }
            else
            {
                if (pList != 0)
                    this->pNode = pList->tail;
                else
                    pNode = 0;
            }
            this->pList = pList;
        }

        Iterator &operator=(const Iterator &iterator)
        {
            this->pNode = iterator.pNode;
            this->pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T) = 0)
        {
            pNode->prev->next = pNode->next;
            pNode->next->prev = pNode->prev;
            Node *pNext = pNode->prev; // MUST prev, so iterator++ will go to end
            if (removeItemData != 0)
                removeItemData(pNode->data);
            delete pNode;
            pNode = pNext;
            pList->count -= 1;
        }

        T &operator*()
        {
            return pNode->data;
        }
        bool operator!=(const Iterator &iterator)
        {
            return pNode != iterator.pNode;
        }
        // Prefix ++ overload
        Iterator &operator++()
        {
            pNode = pNode->next;
            return *this;
        }
        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };

class BWDIterator {
    // TODO implement
private:
  DLinkedList<T>* pList;
  Node* pNode;

public:
  BWDIterator(DLinkedList<T>* pList = nullptr, bool begin = true) {
    if (begin) {
      if (pList != nullptr)
        this -> pNode = pList -> tail -> prev;
      else
        pNode = 0;
    } 
    else {
      if (pList != 0)
        this->pNode = pList -> head;
      else
        pNode = 0;
    }
    this -> pList = pList;
  }

  BWDIterator& operator=(const BWDIterator& iterator) {
    this -> pNode = iterator.pNode;
    this -> pList = iterator.pList;
    return *this;
  }

  T& operator*() { return pNode->data; }

  bool operator!=(const BWDIterator& iterator) {
    return pNode != iterator.pNode;
  }

  BWDIterator& operator++() {
    pNode = pNode -> prev;
    return *this;
  }

  BWDIterator operator++(int) {
    BWDIterator iterator = *this;
    ++*this;
    return iterator;
  }

  void remove(void (*removeItemData)(T) = nullptr) {
    pNode -> prev -> next = pNode -> next;
    pNode -> next -> prev = pNode -> prev;
    Node* pNext = pNode -> next;
    if (removeItemData != 0) {
        removeItemData(pNode -> data);
    }
    delete pNode;
    pNode = pNext;
    pList -> count -= 1;
  }
}; //class BWDI
};
//////////////////////////////////////////////////////////////////////
// Define a shorter name for DLinkedList:

template <class T>
using List = DLinkedList<T>;

//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
DLinkedList<T>::DLinkedList(
    void (*deleteUserData)(DLinkedList<T> *),
    bool (*itemEqual)(T &, T &))
{
    // TODO
    head = new Node();
    tail = new Node();
    head -> next = tail;
    head -> prev = nullptr;
    tail -> prev = head;
    tail -> next = nullptr;
    this -> count = 0;
    this -> deleteUserData = deleteUserData;
    this -> itemEqual = itemEqual;
    //cout<<"Normal 1"<<endl;
}

template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T> &list)
{
    // TODO
    //removeInternalData();
    copyFrom(list);
    //cout<<"Normal 2"<<endl;
}

template <class T>
DLinkedList<T> &DLinkedList<T>::operator=(const DLinkedList<T> &list)
{
    // TODO
    //maybe copyFrom
     if (this != &list){
        removeInternalData();
        copyFrom(list);
    }
    //cout<<"Normal 3"<<endl;
    return *this;
}

template <class T>
DLinkedList<T>::~DLinkedList()
{
    // TODO
    removeInternalData();
    //cout<<"Normal 4"<<endl;
    delete head;
    delete tail;
}

template <class T>
void DLinkedList<T>::add(T e)
{
    // TODO
    Node* newNode = new Node(e, nullptr, nullptr);
        // Add ath the end
        newNode -> prev = tail->prev;
        newNode -> next = tail;
        tail -> prev -> next = newNode;
        tail -> prev = newNode;
        count++;
    //cout<<"Normal 5"<<endl;
}
template <class T>
void DLinkedList<T>::add(int index, T e)
{
    // TODO
    checkIndex(index);
    int movement = 0;
    Node* curr = head -> next;
    if (index == count) {
        add(e);
    }else{
        while (curr != tail && movement < index){
            movement++;
            curr = curr -> next;
        }
    //Node* newNode = new Node(e, curr, curr -> prev);
        Node* newNode = new Node(e, nullptr, nullptr);
        curr -> prev -> next = newNode;
        newNode -> prev = curr -> prev;
        newNode -> next = curr;
        curr -> prev = newNode;
        count++;
    }
}

template <class T>
typename DLinkedList<T>::Node *DLinkedList<T>::getPreviousNodeOf(int index) //checkindex
{
    /**
     * Returns the node preceding the specified index in the doubly linked list.
     * If the index is in the first half of the list, it traverses from the head; otherwise, it traverses from the tail.
     * Efficiently navigates to the node by choosing the shorter path based on the index's position.
     */
    // TODO
    checkRealIndex(index);
    Node* curr = nullptr;
    int movement;
    if (count <= 1) return -1; //so luong be hon 1 thi out ra vi k co prev node?
    if (index <= (count/2)){
        curr = head -> next;
        movement = 0;
        while (curr){
            if (movement == index){
                return curr -> prev;   
        }
            curr = curr -> next;
            movement++;
        }
    }else{
        curr = tail -> prev;
        movement = count - 1;
        while (curr){
            if (movement == index){
                return curr -> prev;   
        }
            curr = curr -> prev;
            movement--;
        }
    }
    return nullptr;
}

template <class T>
T DLinkedList<T>::removeAt(int index) //checkindex
{
    // TODO
    checkRealIndex(index);
    Node* curr = head -> next;
    int movement = 0;
    // if ((curr -> next = tail)){ //node cuoi thi sao? k the noi lai tu dau
    //     head -> next = tail;
    //     tail -> prev = head;
    //     return curr -> data;
    // }
    while (curr != tail){
        if (movement == index){
            T data = curr -> data;
            curr -> next -> prev = curr -> prev;
            curr -> prev -> next = curr -> next;
            curr -> next = nullptr;
            curr -> prev = nullptr;
            count--;
            delete curr;
            return data;
        }
        curr = curr -> next;
        movement++;
    }
    return curr -> data; //dkw
}

template <class T>
bool DLinkedList<T>::empty()
{
    // TODO
    if (count == 0) return true;
    return false;
}

template <class T>
int DLinkedList<T>::size()
{
    // TODO
    return count;
}

template <class T>
void DLinkedList<T>::clear()
{
    // TODO
    removeInternalData();
    // head -> next = tail;
    // tail -> prev = head;
    // count = 0;
}

template <class T>
T &DLinkedList<T>::get(int index) //checkindex
{
    // TODO
    checkRealIndex(index);
   // if (index < 0 || index >= count) throw std::out_of_range("Index is out of range!");
    Node* curr = head -> next;
    int movement = 0;
    while (curr != tail){
        if (movement == index){
            return curr -> data;   
        }
        movement++;
        curr = curr -> next;
    }
    return curr -> data; //dkw
}

template <class T>
int DLinkedList<T>::indexOf(T item)
{
    // TODO
    int index = 0;
    Node* curr = head -> next;
    while (curr != tail){
        if (equals(curr -> data, item, itemEqual)){
            return index;
        }
        index++;
        curr = curr -> next;
    }
    return -1;
}

template <class T>
bool DLinkedList<T>::removeItem(T item, void (*removeItemData)(T))
{
    // TODO
    int index = 0;
    Node* curr = head -> next;
    while (curr != tail){
        if (equals(curr -> data, item, itemEqual)){
            if (removeItemData != nullptr){
                removeItemData(curr -> data);
            }
            //Should deleterighthere
            curr -> next -> prev = curr -> prev;
            curr -> prev -> next = curr -> next;
            curr -> next = nullptr;
            curr -> prev = nullptr;
            delete curr;
            count--;
            return true;
        }
        index++;
        curr = curr -> next;
    }
    return false;
}

template <class T>
void DLinkedList<T>::checkIndex(int index){
    if (index < 0 || index > count){
        throw std::out_of_range("Index is out of range!");
    }    
}

template <class T>
void DLinkedList<T>::checkRealIndex(int index){
    if (index < 0 || index >= count){
        throw std::out_of_range("Index is out of range!");
    }   
}

template <class T>
bool DLinkedList<T>::contains(T item)
{
    // TODO
    if (indexOf(item) != -1) return true;
    return false;
}

template <class T>
string DLinkedList<T>::toString(string (*item2str)(T &))
{
    /**
     * Converts the list into a string representation, where each element is formatted using a user-provided function.
     * If no custom function is provided, it directly uses the element's default string representation.
     * Example: If the list contains {1, 2, 3} and the provided function formats integers, calling toString would return "[1, 2, 3]".
     *
     * @param item2str A function that converts an item of type T to a string. If null, default to string conversion of T.
     * @return A string representation of the list with elements separated by commas and enclosed in square brackets.
     */
    // TODO
    stringstream ss;
    bool isComma = true;
    ss << "[";
    Node* curr = head -> next;
    while (curr != tail){
        if (!isComma){
            ss <<", ";
        }
        isComma = false;
        if (item2str != nullptr){
            ss << item2str(curr -> data);
        }else{
            ss << curr->data;
        }
        curr = curr -> next;
    }
    ss << "]";
    return ss.str();
}

template <class T>
void DLinkedList<T>::copyFrom(const DLinkedList<T> &list)
{
    /**
     * Copies the contents of another doubly linked list into this list.
     * Initializes the current list to an empty state and then duplicates all data and pointers from the source list.
     * Iterates through the source list and adds each element, preserving the order of the nodes.
     */
    // TODO
    //removeInternalData();
    this -> head = new Node();
    this -> tail = new Node();
    head -> next = tail;
    tail -> prev = head;
    Node* curr = list.head->next;
    while (curr != list.tail) {
        this -> add(curr -> data);
        curr = curr -> next; 
    }
    this -> count = list.count;
    this -> itemEqual = list.itemEqual;
    this -> deleteUserData = list.deleteUserData;
}

template <class T>
void DLinkedList<T>::removeInternalData()
{
    /**
     * Clears the internal data of the list by deleting all nodes and user-defined data.
     * If a custom deletion function is provided, it is used to free the user's data stored in the nodes.
     * Traverses and deletes each node between the head and tail to release memory.
     */
    // TODO
    if (deleteUserData != nullptr){
        deleteUserData(this);
    }  
    Node *curr = head -> next;
    while (curr != tail){
        Node *nextNode = curr->next; 
        delete curr; 
        curr = nextNode; 
    }
    count = 0;
    head->next = tail;
    tail->prev = head;
}

#endif /* DLINKEDLIST_H */