template <class T>
T ArrayList<T>::get(int index)
{
    // TODO
     if (index < 0 || index >= count){
        throw std::out_of_range("Index is out of range");
    }
    return data[index];
}


template <class T>
void ArrayList<T>::clear()
{
    // TODO
    removeInternalData();
    data = new T[capacity];
    count = 0;
}

template <class T>
bool ArrayList<T>::empty()
{
    // TODO
    if (count == 0) return true;
    return false;
}

template <class T>
int ArrayList<T>::indexOf(T item)
{
    // TODO
    for (int i = 0; i < count; i++){
        if (equals(data[i],item,itemEqual)){
            return i;
        }
    }
    return -1;
}
template <class T>
bool ArrayList<T>::contains(T item)
{
    // TODO
    if (indexOf(item)!= -1) return true;
    return false;
}

template <class T>
void ArrayList<T>::set(int index, T e){
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is out of range");
    }
    data[index] = e; // Cập nhật phần tử
}

