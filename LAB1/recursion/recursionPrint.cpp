void print(int n, bool checkFirst, int& count){
    if (!checkFirst) cout<<", ";
    checkFirst = false;
    cout << count;
    if ( count == n ) return;
    return print(n, checkFirst, ++count);
}

void printArray(int n)
{
bool checkFirst = true;
int count = 0;
return print(n, checkFirst, count);
}
