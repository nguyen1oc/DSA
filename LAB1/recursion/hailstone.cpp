void printHailstone(int number)
{
    /*  
     * STUDENT ANSWER
     */
    if (number == 1){
        cout<< number;
        return;
    }  
    cout << number <<" ";
    if (number % 2 == 0) return printHailstone(number/2);
    
    else return printHailstone(number * 3 + 1);
}
