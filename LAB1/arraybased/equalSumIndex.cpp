int equalSumIndex(vector<int>& nums) {
    // STUDENT ANSWER
    int right = 0, left = 0;
    for (int i = 0; i < nums.size(); i++){
        right += nums[i];
    }
    for (int i = 0; i < nums.size(); i++){
        right -= nums[i];
        if (right == left) return i; 
        left += nums[i];
    }
    return -1;
}
