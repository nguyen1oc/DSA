void remove(){
    if (cursor = listSize) throw out_of_range(Cannot remove element);
    for (int i = cursor; i  listSize - 1; i++)
        data[i] = data[i + 1];
    listSize--;
}
