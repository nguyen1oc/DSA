template <typename T>
vector<vector<T>> powerSet (vector<T> arr) 
{
    vector<vector<T>> result;
    vector<T> tmp;
    int k = 0, x = 0;

    int size = pow(2, arr.size());
    for (int i = 0; i < size; i++)
    {
        k = 0; x = i;
        tmp.clear();

        while (x) 
        {
            if (x & 1) 
                tmp.push_back(arr[k]);
            x = x >> 1;
            k++;
        }
        result.push_back(tmp);
    }
    return result;
}
