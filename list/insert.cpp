void insert(const T& v){
    for (int i = size++; i > cursor; i--){
                data[i] = data[i-1];
    }            
    data[cursor] = v;  
}
