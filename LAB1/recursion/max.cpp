int maxi(int* arr, int length, int max){
    if (length == 0) return max;
    if (max < arr[length]){
        max = arr[length];
    }
    return maxi(arr, length -1, max);
}
int findMax(int* arr, int length)
{
    /*  
     * STUDENT ANSWER
     */
    int max = arr[0]; 
    return maxi(arr, length - 1, max);
}
