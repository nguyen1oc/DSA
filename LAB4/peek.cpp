template<class T>
int Heap<T>::size(){
  return count;
}

template<class T>
bool Heap<T>::isEmpty(){
 return count == 0;
}

template<class T>
T Heap<T>::peek(){
 if (count == 0) throw std::underflow_error("Calling to peek with the empty heap.");
  return elements[0];
}

template<class T>
bool Heap<T>::contains(T item){
     for (int i = 0; i < count; i++) {
        if (elements[i] == item) {
            return true;
        }
    }
    return false;

}

template<class T>
bool Heap<T>::pop(){
  if (count == 0) throw std::underflow_error("Calling to peek with the empty heap.");
  T ini = elements[0];
  elements[0] = elements[count - 1];
  count--;
  reheapDown(0);
  return ini;
}
