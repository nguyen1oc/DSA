int Fib(const int n) {
    /* To do */
    if (n <= 1) return 1;
    int res = 1, temp = 1;
    AStack<int> as;
    as.push(temp);
    for (int i = 0; i < n; i++){
        temp = res;
        res += as.pop();
        as.push(res);
    }
    return res;
}

int Fib(const int n)
{
    /* To do */
    if (n <= 1) return 1;

    int res = 1, temp = 1;
    AStack<int> fibo;
    fibo.push(temp);

    for (int i = 0; i < n - 1; i++)
    {
        temp = res;
        res += fibo.pop();
        fibo.push(temp);
    }

    return res;
}
