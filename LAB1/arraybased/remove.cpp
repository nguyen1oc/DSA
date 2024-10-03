template <class T>
T ArrayList<T>::removeAt(int index)
{
    if (index < 0 || index >= count){
        throw std::out_of_range("Index is out of range!");
    }
    T removeE = data[index];
    for (int i = index; i < count - 1; i++){
        data[i] = data[i + 1];
    }
    count--;
    return removeE;
}

template<class T>
bool ArrayList<T>::removeItem(T item){
     /* Remove the first apperance of item in array and return true, otherwise return false */
     for (int i = 0; i < count; i++){
        if (item == data[i]){
            removeAt(i);
            return true;
        }
    }
    return false;
    
}

template<class T>
void ArrayList<T>::clear(){
    /* 
        Delete array if array is not NULL
        Create new array with: size = 0, capacity = 5
    */
    delete []data;
    data = nullptr;
    count = 0;
    data = new T[capacity];
}
