int myArrayToInt(char *str, int n) 
{ 
    /*  
     * STUDENT ANSWER
     */ 
    if (n == 0) return 0;
    int current_digit = str[n - 1] - '0';
    return myArrayToInt(str, n - 1) * 10 + current_digit;
}
