template <typename T>

int findMax(T arr[],int n){
    T max = 0, index;
    for (int i = 0; i < n; i++){
        if (arr[i] >= max){
            max = arr[i];
            index = i;
        }
    }
    return index;
}
