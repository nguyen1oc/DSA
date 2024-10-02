void enqueue(const E& it){
    if ((rear + 2) % maxSize == front) throw out_of_range("Queue is full");
    rear = (rear + 1) % maxSize;
    listArray[rear] = it
}
