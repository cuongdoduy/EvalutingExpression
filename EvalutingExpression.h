#ifndef __EVALUTINGEXPRESSION_H__
#define __EVALUTINGEXPRESSION_H__
#include <iostream>
#include <string>
#include<bits/stdc++.h>
using namespace std;
template<typename T>
class Stack 
{
private:
    T* data;
    int capacity;
    int top;
public:
    Stack(int cap = 100) {
        data = new T[cap];
        capacity = cap;
        top = -1;
    }
    ~Stack() {
        delete[] data;
    }
    T Top()
    {
         if (top== -1) {
            cout << "Stack is empty!" << endl;
            return T();
        }
        return data[top];
    }
    void push(T val) {
        if (top == capacity - 1) {
            // double the capacity
            T* temp = new T[2 * capacity];
            for (int i = 0; i < capacity; i++) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
            capacity *= 2;
        }
        data[++top] = val;
    }
    T pop() {
        if (top == -1) {
            // throw an exception or return a default value
            return T();
        }
        return data[top--];
    }
    bool empty() {
        return (top == -1);
    }
};

class Data
{
    private:
    string name;
    int value;
    public:
    void Construct(string name,int value);
    string getName();
    int getValue();
};

string Infix2Postfix(string infix);
string Infix2Prefix(string infix);
string PostfixPrefixCalculator(string input);

string LogicInfix2Postfix(string infix);
string LogicInfix2Prefix(string infix);
string LogicPostfixPrefixCalculator(string input,string varlue);

// More functions declare here

int priority (char alpha);
int priorityForLogic(string s);
bool isOperator(char x);
bool isOperatorLogic(string x);
float convertStringtoNum(string s);
Data* HandleVarlue(string s,int &n);
string preToPost(string pre_exp);
string preToPostLogical(string pre_exp);

#endif // __EVALUTINGEXPRESSION_H__