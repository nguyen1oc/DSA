bool recursive(const char*s, AStack<char>& in){
    if(*s == '\0') return in.length() == 0;
    if(*s == '(') in.push (*s);
    if(*s == ')'){
        if(in.length() == 0) return false;
        else in.pop();
    }
    return recursive(s + 1, in);
}
bool recursiveParentheses(const string &L) {
    /* to check if the string L includes balanced parentheses or not */
    AStack<char>in;
    return recursive(&L[0], in);
}
    
