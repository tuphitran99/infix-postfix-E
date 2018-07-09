/*
   Tu Tran
   Programming II
   Due: July 9, 18
   Evaluate postfix
   Evaluate value of postfix expression
 */
 #include <iostream>
 #include <fstream>
 #include <string>
 #include <math.h>
 #include "mystack.cpp"
using namespace std;

int precedence(char s){
	if ( s == '^' ) return 3;
	else if ( s == '*' ) return 2;
	else if ( s == '/' ) return 2;
	else if ( s == '+' ) return 1;
	else if ( s == '-' ) return 1;
	else if ( s == '(' ) return 0;
	else return 0;
};

int priority(char st, char top){// --- evaluate priority
	int a, b;
	a = precedence(st);
	b = precedence(top);

	return b-a;
};

double evaluate (int a, char doge, int b){// --- evaluate result
	double result;
	switch (doge)
	{
	case '+': result = a + b; break;
	case '-': result = a - b; break;
	case '*': result = a * b; break;
	case '/': result = a / b; break;
	case '^': result = pow(a,b); break;
	}
	return result;
}

void processData(){
	ifstream file, file1;
	file.open("data.txt");  // --- data file

	ofstream writeFile;

	string st;
	string doge;

	char temp;
	stack <char> stk(100);

	int a, b, x;
	double result;
	string number;
	stack <int> num(100);


	while (getline(file, st)) {
		writeFile.open("postfix.txt");    // --- write postfix to file
		cout << st <<endl;
		//----------------------CONVERT TO POSTFIX -------------------
		for (int i = 0; i < st.length(); i++) {
			if ( st[i] == *(" ") ) continue;      //skip blank
			else{
				if(isdigit(st[i])) {
					cout << st[i];
					writeFile << st[i];          /*write to file*/
				}
				else {
					if ( st[i]== *("(") ) {stk.push(st[i]);}
					else {

						if ( st[i]== *(")") ) {
							while ( stk.topVal() != '(' && !stk.isEmpty() ) {
								stk.pop(temp);
								cout << temp;
								writeFile << temp;                /*write to file*/
							}
							stk.pop(temp);
						}
						else {

							if (stk.isEmpty()) {stk.push(st[i]);}
							else {
								while (!stk.isEmpty() && priority(st[i], stk.topVal()) >=0) {
									stk.pop(temp);
									cout << temp;
									writeFile << temp;                  /*write to file*/
								}
								stk.push(st[i]);
							}
						}
					}
				}
			}
		}
		while(!stk.isEmpty()) {
			stk.pop(temp);
			cout << temp;
			writeFile << temp;      /*write to file*/
		}
		cout << endl;
		writeFile << endl;    /*write to file*/

		// ------------- EVALUATE POSTFIX------------------ //
		file1.open("postfix.txt");
		while (getline(file1, doge)) {    // -- doge is just a string container
			for (int i = 0; i < doge.length(); i++) {
				if(isdigit(doge[i])) {
					number = doge[i];
					x = stoi(number);
					num.push(x);
				}

				else{
					num.pop(a);
					num.pop(b);
					result = evaluate(b, doge[i], a);
					num.push(result);
				}
			}

			if(doge.length() > 1) {cout << result << endl;}      // -- skip blank line
			else continue;
		}

		file1.close();
		writeFile.close();
	}
	file.close();
}

int main(){
	processData();
	return 0;
}
