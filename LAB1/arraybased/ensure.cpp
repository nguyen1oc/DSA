#include <cstring>

template<class T>
void ArrayList<T>::ensureCapacity(int index)
{
     if (index >= capacity){
        if (capacity == 0) capacity = 1;
        int newCap = capacity;
        while (newCap <= index){
            newCap *= 1.5;
        }
        try{
            T* newData = new T[newCap];
            for (int i = 0; i < newCap; i++){
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCap;
        }catch(const std::bad_alloc& e){
            std::cerr<<"Memory allocation failure (in ensure)"<<e.what()<<endl;
            throw;
        }
    }else if (index < 0){
        throw std::out_of_range("Index is out of range!");
    }
}

template <class T>
void ArrayList<T>::add(T e) 
{
    ensureCapacity(count + 1);
    data[count] = e;
    ++count;
}

template<class T>
void ArrayList<T>::add(int index, T e)
{
    ensureCapacity(index);
    ensureCapacity(count + 1);
     if (index >= count){
        add(e);
    }else{
     for (int i = count; i > index; i--){
            data[i] = data[i - 1];
        }
    data[index] = e;
    ++count;
    }
}

template<class T>
int ArrayList<T>::size() 
{
    return count;
}
