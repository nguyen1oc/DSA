string reverseSentence(string s) {
    // STUDENT ANSWER
    if (s.find(' ') == string::npos) return s;
    else{
        int space = s.find(' ');
        string front = s.substr(0, space);
        string reverse = reverseSentence(s.substr(space+1));
        return reverse + ' ' + front;
    }
}
