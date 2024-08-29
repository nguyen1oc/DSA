#include <iostream>
#include <sstream>
#include <string.h>
using namespace std;

string infix_cal (const string & input)
{
	stringstream ss(input);
	int op1, op2; 
	char op;

	ss >> op1 >> op >> op2;
	switch (op)
	{
		case '+': return to_string(op1 + op2);
		case '-': return to_string(op1 - op2);
		case '*': return to_string(op1 * op2);
		case '/': 
		if (op2 == 0) return "invalid";
		return to_string(op1/op2);
		default: return "invalid";
	}
}

int main() {
    string input;
    
    cout << "Enter an infix expression (e.g., '3 + 4'): ";
    getline(cin, input);

    string result = infix_cal(input);
    cout << "Result: " << result << endl;

    return 0;
}
