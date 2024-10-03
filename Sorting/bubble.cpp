template <typename E> 
void bubbleSort(List<E> &L){
    for (int i = 0; i < L.length() - 1; i++){
        for (int j = 0; j < L.length() - i - 1; j++){
            L.moveToPos(j);
            int temp = L.getValue();
            L.moveToPos(j + 1);
            int temp2 = L.getValue();
            if (temp > temp2){
                L.moveToPos(j);
                L.remove(); 
                L.insert(temp2); 
                L.moveToPos(j + 1);
                L.remove();
                L.insert(temp); 
            }
        }
    }
}
