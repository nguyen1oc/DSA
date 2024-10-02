bool parentheses(const string &L) {
    /* To do */
    AStack<char>as;
    for (unsigned int i = 0; i < L.length(); i++){
        if (L[i] == '(') as.push(L[i]);
        if (L[i] == ')'){
            if (as.length() == 0) return false;
            else as.pop();
        }
    }
    return as.length() == 0;
}

bool parentheses(const string &L) {
    /* To do */
    bool confirm = true;
    Stack<char>* as = new AStack<char>(); 
    for (unsigned int i = 0; i < L.length(); i++){
        if (L[i] == '(') as -> push(L[i]);
        if (L[i] == ')'){
            if (as -> length() == 0) return false;
            else as -> pop();
        }
    }
    if (as -> length() == 0) return confirm = true;
    else confirm = false;
    delete as;
    return confirm;
}
