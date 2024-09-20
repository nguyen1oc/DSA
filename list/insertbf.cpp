void insertBefore(const T& v, const T& k) {
    if (listSize == MAXSIZE) throw out_of_range("out of range");
    for (int i = 0; i < listSize; i++) 
            {
                if (data[i] == k) 
                {
                    for (int j = listSize++; j > i; j--)
                        data[j] = data[j - 1];
                    
                    data[i] = v;
                    cursor = i;
                    return;
            }
    }
}
