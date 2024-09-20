 int count = 0;
    
    for (L.moveToStart(); L.currPos() < L.length(); L.next())
        if (L.getValue() == K)
            count++;
    
    return count;
