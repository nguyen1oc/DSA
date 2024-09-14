class Exp {
public:
    virtual ~Exp() {}
    virtual int eval() = 0; 
    virtual void printPrefix() = 0;
};


class BinExp : public Exp {
private:
    Exp* left;  
    char op;    
    Exp* right; 

public:
    BinExp(Exp* left, char op, Exp* right)
        : left(left), op(op), right(right) {}

    ~BinExp() {
        delete left;
        delete right;
    }

    int eval() override {
        int leftVal = left->eval();   
        int rightVal = right->eval(); 

        switch (op) {
            case '+': return leftVal + rightVal;
            case '-': return leftVal - rightVal;
            case '*': return leftVal * rightVal;
            case '/': return leftVal / rightVal;
            default: return -1;
        }
    }
    
    void printPrefix() override{
        cout<<op<<" ";
        left->printPrefix();
        right->printPrefix();
    }
};

class UnExp : public Exp {
private:
    char op;   
    Exp* exp;  

public:
    UnExp(char op, Exp* exp)
        : op(op), exp(exp) {}

    ~UnExp() {
        delete exp;
    }

    int eval() override {
        int value = exp->eval(); 

        switch (op) {
            case '+': return value;  
            case '-': return -value; 
            default: return -1;
        }
    }
    
    void printPrefix() override{
        cout<<op<<". ";
        exp->printPrefix();
    }
};

class IntLit : public Exp {
private:
    int value;

public:
    IntLit(int v) : value(v) {}

    int eval() override {
        return value;
    }
    void printPrefix() override{
       cout << value << " ";
    }
};
