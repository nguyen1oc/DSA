bool is_the_same(const string& word1, const string& word2){
    return word1[0] == word2[0];
}

int longestSublist(vector<string>& words) {
    // STUDENT ANSWER
    if ( words.size() == 0) return 0;
    int curr = 1, max_curr = 0;
    for (int i = 1; i < words.size(); i++){
        if (is_the_same(words[i-1], words[i])) curr++;
        else{
            if (curr > max_curr) max_curr = curr;
            curr = 1;
        } 
    }
    return max(curr, max_curr);
}
