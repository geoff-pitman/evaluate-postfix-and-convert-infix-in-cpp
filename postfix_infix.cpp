// Author: Geoffrey Pitman
// Date: 9/21/2016

#include <iostream>
#include <stack>

using namespace std;

// evaluate a postfix expression and print result
void evalPostfix(string);
// identifies operator precedence, or operand
int getPrecedence(char c);
// convert infix expression to postfix expression and print result
void convertInfix(string);

int main()
{
    string expression;
	int choice = 0;
	
	while (1)
	{
		cout << "Enter your options [1]evaluate postfix  [2]convert infix to postfix: ";
		cin >> choice;
		
		if (choice == 1)
		{
			cout << "Enter postfix expression: ";
			cin >> expression;
			evalPostfix(expression);
		}	
		else if (choice == 2)
		{
			cout << "Enter infix expression: ";
			cin >> expression;
			convertInfix(expression);
		}
	
	}
	cout << endl << endl;
	return 0;
}

// evaluate a postfix expression and print result
void evalPostfix(string exp) 
{    
   stack<int> st;
   int op1 = 0, op2 = 0, result = 0;
   
   for (int idx = 0; idx < exp.length(); idx++)
   {
      if (exp[idx] != '*' && exp[idx] != '+' && exp[idx] != '-') 
		 st.push(exp[idx]-'0');
      else 
      {
         op1 = st.top();
         st.pop();
         op2 = st.top();
         st.pop();
		 
	  if (exp[idx] == '*') result = op2 * op1;
	  else if (exp[idx] == '+') result = op2 + op1;
	  else if (exp[idx] == '-') result = op2 - op1;
	  else cout << "error" << endl;
		 
	   st.push(result);
	}
    }
    cout << endl << "Value of the expression: " << result << endl << endl;
}

// returns/identifies operator precedence, or operand
int getPrecedence(char op)
{
    if (op == '*') return 2;
    else if (op == '+') return 1;
    else return 0; // if operand
}

// convert infix expression to postfix expression and print result
void convertInfix(string exp) 
{
   stack<char> st;
   string postfix = "";
   int precedence = 0, position = 0;

   for (int idx = 0; idx < exp.length(); idx++)
   {
      if (exp[idx] == '(') 
      {
         st.push(exp[idx]);
         continue;
      }
      if (exp[idx] == ')') 
      {
         while (!st.empty() && st.top() != '(') 
	 {
            postfix += st.top();
            st.pop();
         }
         if (!st.empty()) 
            st.pop();
         continue;
      }
      precedence = getPrecedence(exp[idx]);
      if (!precedence) 
         postfix += exp[idx];
      else 
      {
         if (st.empty())
            st.push(exp[idx]);
         else 
	 {
            while (!st.empty() && st.top() != '(' && precedence <= getPrecedence(st.top())) 
	    {
               postfix += st.top();
               st.pop();
            }
            st.push(exp[idx]);
         }
      }
   }
   while (!st.empty()) 
   {
      postfix += st.top();
      st.pop();
   }
   cout << endl << "Postfix expression: " << postfix << endl << endl;
}
