E removePre(){
    E deleteN;
    Assert(curr != head, "No element");
    Link<E>* thisN = curr;
    deleteN = thisN -> element;
    curr -> next -> prev = thisN -> prev;
    curr -> prev -> next = thisN -> next;
    curr = curr -> prev;
    delete thisN;
    return deleteN;
}
