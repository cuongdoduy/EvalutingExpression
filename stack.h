#include<main.h>
template<typename T>
class Stack {
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
