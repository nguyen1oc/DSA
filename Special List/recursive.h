bool recursive(const char* s, Stack<char>& in) {
    if (*s == '\0') return in.length() == 0;  

    if (*s == '(') in.push(*s); 

    if (*s == ')'){
        if (in.length() == 0) return false;  
        else in.pop(); 
    }
    return recursive(s + 1, in); 
}

bool recursiveParentheses(const string &L) {
    Stack<char>* in = new AStack<char>();  
    bool result = recursive(&L[0], *in); 
    delete in;  
    return result;
}
