#include<iostream>
#include<string>
#include<bits/stdc++.h>
using namespace std;
int priority (char alpha)
{
    if(alpha == '+' || alpha =='-')
        return 1;
 
    if(alpha == '*' || alpha =='/')
        return 2;
    if(alpha == '^')
        return 3;
    return 0;
}
struct Node
{
    char data;
    Node *next;
};
Node *CreateNode(char init)
{
    Node *node = new Node;
    node->data = init;
    node->next = NULL;
    return node;
}
struct Stack
{
    Node *head;
};
void CreateStack(Stack &s)
{
    s.head = NULL;
}
bool IsEmpty(Stack s)
{
    if (s.head == NULL)
        return true;
    return false;
}
void Push(Stack &s, Node *node)
{
    if (s.head == NULL)
        s.head = node;
    else
    {
        node->next = s.head;
        s.head = node;
    }
}
char Pop(Stack &s)
{
    if (IsEmpty(s))
        return 0; 
    Node *node = s.head;
    char data = node->data; // lưu trữ lại giá trị của node
    s.head = node->next;
    delete node;   // hủy node
    return data;
}
char Top(Stack s)
{
    if (IsEmpty(s))  return 0;
    return s.head->data;
}
int main(int argc, char ** argv)
{
    string file_input(argv[1]);
    string s,num="",postfix="",calculation="";
    Stack stack;
    CreateStack(stack);
    int i=0;
    ifstream ReadFile(file_input);
    ReadFile>>s;
    string str=s;
    reverse(str.begin(), str.end());
    for(int i=str.length()-1;i>=0;i--)
    {
        if(str[i]=='(')
        {
            str[i]=')';
        }
        else if(str[i]==')')
        {
            str[i]='(';
        }
    }
    s=str;
    int n=s.length();
    while(i<n)
    {
        if (s[i]!='+'&&s[i]!='-'&&s[i]!='*'&&s[i]!='/' &&s[i]!='('&&s[i]!=')'&&(s[i]!='^'))
        {
            num+=s[i];
        }
        else if (s[i]=='(')
        {
            Node *node = CreateNode(s[i]);
            Push(stack, node);
        }
        else if (s[i]==')')
        {
            num!=""?postfix+=num+" ":"";
            while(Top(stack)!='(')
            {
                
                calculation=Top(stack);
                postfix += calculation+" ";
                Pop(stack);
            }
            Pop(stack);
            num="";
        }
        else
        {
            string syntax;
            num!=""?postfix+=num+" ":"";
            while (IsEmpty(stack)==false && priority(s[i]) < priority(Top(stack)))
            {
                calculation=Top(stack);
                postfix += calculation+" ";
                Pop(stack);
            }
            Node *node = CreateNode(s[i]);
            Push(stack,node);
            num="";
        }
        i++;
    }
    num!=""?postfix+=num+" ":"";
    while(IsEmpty(stack)==false)
    {
        calculation=Top(stack);
        postfix+=calculation+" ";        
        Pop(stack);
    }
    str="";
    i=0;
    reverse(postfix.begin(), postfix.end());
    while(postfix[i]==' ') i++;
    for(i;i<postfix.length();i++)
    str+=postfix[i];
    cout<<str;
    return 0;
}