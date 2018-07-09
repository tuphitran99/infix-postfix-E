// ------- STACK CREATED BY -----------//
// ----- PROF. McDaniel ------------//
#include <iostream>
using namespace std;
template<typename T>

class stack {
T *st;
int top;
int size;
public:
stack(int i)
{
	st = new T[i];
	top = -1;
	size = i;
}
~stack()
{
	delete [] st;
}
void push(T i)
{
	st[++top] = i;
}
void pop(T &i)
{
	i = st[top--];
}
int sizeof_()
{
	return size;
}
int items()      // number of items on the stack
{
	return top;
}
int isEmpty(){
	if (top <0) return 1;
	else return 0;
}
T topVal(){
	return st[top];
}
};
