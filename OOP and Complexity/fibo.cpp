unsigned int fibo(int n){
    if (n == 1) return 1;
    if (n == 0) return 0;
    unsigned int fibonan[128] ={0,1};
    for (int i = 2; i <= n; i++){
       fibonan[i] = fibonan[i-1] + fibonan[i-2];
    }
    return fibonan[n];
}
