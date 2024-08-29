#include<sstream>
#include<string.h>
using namespace std;

struct action 
{
    string op; // oprator
    int (*func)(int, int); // function pointer to corresponding function
};

int myadd(int x, int y) { return x + y; }
int mymin(int x, int y) { return x - y; }
int mymul(int x, int y) { return x * y; }
int mydiv(int x, int y) { return x / y; }


int infix_cal(const string & input){
    int op1, op2, result = 0;
    string op = "";
    stringstream ss(input);
    ss >> op1 >> op >> op2;
    action actions[] = {
        { "+", myadd },
        { "-", mymin },
        { "*", mymul },
        { "/", mydiv }
    };
    for (int i = 0; i < 4; i++)
        if (actions[i].op == op)
            result = actions[i].func(op1,op2);
        
    return result;
}

int main ()
{
	cout << infix_cal("10 + 4");
	return 0;
}
