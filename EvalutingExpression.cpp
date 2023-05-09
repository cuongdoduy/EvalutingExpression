#include "EvalutingExpression.h"

// Implement function  for class Data
void Data::Construct(string name,int value)
{
    this->name=name;
    this->value=value;
}
string Data::getName()
{
    return name;
}
int Data::getValue()
{
    return value;
}
// End of class Data


//  Declare more function needed
float convertStringtoNum(string s)
{
    float num=0;
    for(int i=0;i<s.length();i++)
    {
        num=num*10+(s[i]-'0');
    }
    return num;
}
bool isOperator(char x)
{
    switch (x) {
    case '+':
    case '-':
    case '/':
    case '*':
    case '^':
    case '|':
    case '&':
    case '~':
        return true;
    }
    return false;
}
bool isOperatorLogic(string x)
{
    if (x=="&"||x=="|"||x=="~"||x=="->"||x=="<->") return true;
    return false;
}
int priority (char alpha)
{
    if(alpha == '+' || alpha =='-')
    return 1;
    if(alpha == '*' || alpha =='/')
    return 2;
    if(alpha == '^')
    return 3;
    if(alpha == '&'||alpha == '|')
    return 4;
    if(alpha == '~')
    return 5;
    return 0;
}
int priorityForLogic(string s)
{
    if (s == "<->")return 2;
    if (s == "->")return 3;
    if(s == "&"||s == "|")
    return 4;
    if(s == "~")
    return 5; 
    return 0;
}
string preToPost(string pre_exp)
{
    Stack<string> s;
    string num="";
    // length of expression
    int length = pre_exp.size();
    // reading from right to left
    for (int i = length - 1; i >= 0; i--)
    {
        // check if symbol is operator
        if (isdigit(pre_exp[i])) {
            // push operand to stack
            string op(1, pre_exp[i]);
            num+=op;
            if (pre_exp[i-1]==' ') {
                reverse(num.begin(),num.end());
                s.push(num);
                num="";
            }
        }
        else if (isOperator(pre_exp[i]))
        {
            // pop two operands from stack
            string op1 = s.Top();
            s.pop();
            string op2 = s.Top();
            s.pop();
 
            // concat the operands and operator
            string temp = op1 + op2 + " " + pre_exp[i];
            // Push string temp back to stack
            s.push(temp);
        }
    }
    // stack contains only the Postfix expression
    return s.Top();
}
string preToPostLogical(string pre_exp)
{
    Stack<string> s;
    string num="";
    string syntax="";
    // length of expression
    int length = pre_exp.size();
    // reading from right to left
    for (int i = length - 1; i >= 0; i--)
    {
        // check if symbol is operator
        if (pre_exp[i]=='>'&&pre_exp[i-1]=='-' && pre_exp[i-2]=='<')
        {
            syntax="<->";
            i-=2;
        }
        else if (pre_exp[i]=='>'&&pre_exp[i-1]=='-')
        {
            syntax="->";
            i--;
        }
        else syntax=pre_exp[i];
        if (isOperatorLogic(syntax))
        {
            // pop two operands from stack
            if(syntax=="~")
            {
                string op1 = s.Top();
                s.pop();
                // concat the operands and operator
                string temp = op1+ syntax;
                // Push string temp back to stack
                s.push(temp);
            }
            else
            {
                string op1 = s.Top();
                s.pop();
                string op2 = s.Top();
                s.pop();
                // concat the operands and operator
                string temp = op1 + op2 + syntax;
                // Push string temp back to stack
                s.push(temp);
            }
        }
        else
        {
            string op(1, pre_exp[i]);
            s.push(op);
        }
        
    }
    // stack contains only the Postfix expression
    return s.Top();

}
Data* HandleVarlue(string s,int &count)
{
    Data *data;
    data =new Data[10000];
    int j=0,n=s.length();
    string name;
    while(!isdigit(s[j])) j++;
    for(int i=0;i<j;i++)
        {
            if(s[i]!=' ')
            {
                while(j<n)
                {
                    if(s[j]!=' ')
                    {
                        string num;
                        name=s[i];
                        num=s[j];
                        data[count].Construct(name,stoi(num));
                        count++;
                        j++;
                        break;
                    }
                    j++;
                }
            }
        }
        return data;
}
// End of declare function

// Implement function for Expression
string Infix2Postfix(string infix)
{
    string s="",num="",postfix="",calculation="";
    Stack<char>stack;
    s=infix;
    int i=0,n=s.length();
    while(i<n)
    {
        if (s[i]!='+'&&s[i]!='-'&&s[i]!='*'&&s[i]!='/' &&s[i]!='('&&s[i]!=')'&&(s[i]!='^'))
        {
            num+=s[i];
        }
        else if (s[i]=='(')
        {
            stack.push(s[i]);
        }
        else if (s[i]==')')
        {
            num!=""?postfix+=num+" ":"";
            while(stack.Top()!='(')
            {
                
                calculation=stack.Top();
                postfix += calculation+" ";
                stack.pop();
            }
            stack.pop();
            num="";
        }
        else
        {
            string syntax;
            num!=""?postfix+=num+" ":"";
            while (stack.empty()==false && priority(s[i]) <= priority(stack.Top()))
            {
                calculation=stack.Top();
                postfix += calculation+" ";
                stack.pop();
            }
            stack.push(s[i]);
            num="";    
        }
        i++;
    }
    num!=""?postfix+=num+" ":"";
    while(stack.empty()==false)
    {
        calculation=stack.Top();
        postfix += calculation+" ";
        stack.pop();
    }
    return postfix;
}
string Infix2Prefix(string infix)
{
    string s="",num="",postfix="",calculation="";
    Stack<char>stack;
    s=infix;
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
    int i=0,n=s.length();
    while(i<n)
    {
        if (s[i]!='+'&&s[i]!='-'&&s[i]!='*'&&s[i]!='/' &&s[i]!='('&&s[i]!=')'&&(s[i]!='^'))
        {
            num+=s[i];
        }
        else if (s[i]=='(')
        {
            stack.push(s[i]);
        }
        else if (s[i]==')')
        {
            num!=""?postfix+=num+" ":"";
            while(stack.Top()!='(')
            {
                
                calculation=stack.Top();
                postfix += calculation+" ";
                stack.pop();
            }
            stack.pop();
            num="";
        }
        else
        {
            string syntax;
            num!=""?postfix+=num+" ":"";
            while (stack.empty()==false && priority(s[i]) < priority(stack.Top()))
            {
                calculation=stack.Top();
                postfix += calculation+" ";
                stack.pop();
            }
            stack.push(s[i]);
            num="";    
        }
        i++;
    }
    num!=""?postfix+=num+" ":"";
    while(stack.empty()==false)
    {
        calculation=stack.Top();
        postfix += calculation+" ";
        stack.pop();
    }
    str="";
    i=0;
    reverse(postfix.begin(), postfix.end());
    while(postfix[i]==' ') i++;
    n=postfix.length();
    for(int k=i;k<n;k++)
    str+=postfix[k];
    return str;    
}
string PostfixPrefixCalculator(string input)
{
    string s,num="",postfix="",calculation="";
    Stack<long double> stack;
    int i=0;
    s=input;
    if (s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^') 
    s=preToPost(s);
    int n=s.length();
    while(i<n)
    {
        if (s[i]!='+'&&s[i]!='-'&&s[i]!='*'&&s[i]!='/'&&s[i]!='^'&&(s[i]!=' '))
        {
            num+=s[i];
        }
        else if(s[i]==' '&&num!="")
        {
                long double number=convertStringtoNum(num);
                stack.push(number);
                num="";
        }
        else if (s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^')
        {
           
            long double x=stack.Top();
            stack.pop();
            long double y=stack.Top();
            stack.pop();
            if(s[i]=='+')
            {
                stack.push(x+y);
            }
            else if(s[i]=='-')
            {
                stack.push(y-x);
            }
            else if(s[i]=='*')
            {
                stack.push(x*y);
            }
            else if(s[i]=='/')
            {
                stack.push(y/x);
            }
            else if (s[i]=='^')
            {
                stack.push(pow(y,x));
            }
        }
        i++;
    }
    if (num!="")
    {
        long double number=convertStringtoNum(num);
        stack.push(number);
    }
    double x = stack.Top();
    int decimal_places = 4;
    double power_of_10 = pow(10, decimal_places);
    double rounded_x = round(x * power_of_10) / power_of_10;
    string result=to_string(rounded_x);
    i=result.length()-1;
    while(result[i]=='0')
    {
        i--;
    }
    if (result[i]=='.')
    {
        i--;
    }
    for(int j=0;j<=i;j++)
    {
        calculation+=result[j];
    }
    return calculation;
}
// End function for Expression

// Implement function for Logical Expression
string LogicInfix2Postfix(string infix)
{
    string s="",num="",postfix="",calculation="";
    Stack<string>stack;
    string syntax;
    infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
    s=infix;
    int i=0,n=s.length();
    while(i<n)
    {
        if (s[i]!='&'&&s[i]!='~'&&s[i]!='|'&&s[i]!='('&&s[i]!=')'&&s[i]!='-'&&s[i]!='<')
        {
            num+=s[i];
        }
        else if (s[i]=='(')
        {
            syntax=s[i];
            stack.push(syntax);
        }
        else if (s[i]==')')
        {
            num!=""?postfix+=num:"";
            while(stack.Top()!="(")
            {
                
                calculation=stack.Top();
                postfix += calculation;
                stack.pop();
            }
            stack.pop();
            num="";
        }
        else
        {
            num!=""?postfix+=num:"";
            if (s[i]=='<')
            {
                syntax="<->";
                i+=2;
            }
            else if (s[i]=='-')
            {
                syntax="->";
                i++;
            }
            else
            {
                syntax=s[i];
            }
            while (stack.empty()==false && priorityForLogic(syntax) <= priorityForLogic(stack.Top()))
            {
                calculation=stack.Top();
                postfix += calculation;
                stack.pop();
            }
            stack.push(syntax);
            num="";    
        }
        i++;
    }
    num!=""?postfix+=num:"";
    while(stack.empty()==false)
    {
        calculation=stack.Top();
        postfix += calculation;
        stack.pop();
    }
    return postfix;
}
string LogicInfix2Prefix(string infix)
{
    string s="",num="",postfix="",calculation="";
    Stack<string>stack;
    int size=0;
    string syntax;
    infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
    s=infix;
    string str=s;
    size=str.length();
    reverse(str.begin(), str.end());
    for(int i=0;i<size;i++)
    {
        if(str[i]=='(')
        {
            str[i]=')';
        }
        else if(str[i]==')')
        {
            str[i]='(';
        }
        else if (str[i]=='<')
        {
            str[i]='>';
        }
        else if (str[i]=='>')
        {
            if (str[i+1]=='-'&&(str[i+2]!='<'))
            {
                str[i]='-';
                str[i+1]='<';
            }
            else  str[i]='<';
        }
    }
    s=str;
    int i=0,n=s.length();
    while(i<n)
    {
        if (s[i]!='&'&&s[i]!='~'&&s[i]!='|'&&s[i]!='('&&s[i]!=')'&&s[i]!='-'&&s[i]!='<')
        {
            num+=s[i];
        }
        else if (s[i]=='(')
        {
            stack.push("(");
        }
        else if (s[i]==')')
        {
            num!=""?postfix+=num:"";
            while(stack.Top()!="(")
            {
                calculation=stack.Top();
                postfix += calculation;
                stack.pop();
            }
            stack.pop();
            num="";
        }
        else
        {
            num!=""?postfix+=num:"";
            if (s[i]=='<')
            {
                syntax="<->";
                i+=2;
            }
            else if (s[i]=='-')
            {
                syntax="->";
                i++;
            }
            else
            {
                syntax=s[i];
            }
            while (stack.empty()==false && priorityForLogic(syntax) < priorityForLogic(stack.Top()))
            {
                calculation=stack.Top();
                postfix += calculation;
                stack.pop();
            }
            stack.push(syntax);
            num="";    
        }
        i++;
    }
    num!=""?postfix+=num:"";
    while(stack.empty()==false)
    {
        calculation=stack.Top();
        postfix += calculation;
        stack.pop();
    }
    str="";
    i=0;
    reverse(postfix.begin(), postfix.end());
    while(postfix[i]==' ') i++;
    n=postfix.length();
    for(int k=i;k<n;k++)
    {
        if (postfix[k]=='>' && postfix[k+1]=='-' && postfix[k+2]=='<')
        {
            str+="<->";
            k+=2;
        }
        else if (postfix[k]=='>' && postfix[k+1]=='-')
        {
            str+="->";
            k+=1;    
        }
        else str+=postfix[k];
    }
    return str;   
}
string LogicPostfixPrefixCalculator(string input,string varlue)
{
    string s,postfix="",ss="";
    int num=0,length=0;
    Data *data=HandleVarlue(varlue,length);
    Stack<int> stack;
    int i=0;
    s=input;
    if (s[i]=='&'||s[i]=='~'||s[i]=='|'||s[i]=='-'||s[i]=='<')
    {
        s=preToPostLogical(s);
    }
    int n=s.length();
    while(i<n)
    {
        if (s[i]!='&'&&s[i]!='~'&&s[i]!='|'&&s[i]!=' '&&s[i]!='<' && s[i]!='-')
        {            
            ss=s[i];
            for(int i=0;i<length;i++)
            {
                if(ss==data[i].getName())
                {
                    stack.push(data[i].getValue());
                }
            }
        }
        else if (s[i]=='&'||s[i]=='~'||s[i]=='|')
        {           
            if(s[i]=='&')
            {
                int  x=stack.Top();
                stack.pop();
                int  y=stack.Top();
                stack.pop();
                stack.push(x&&y);
            }
            else if(s[i]=='~')
            {
                int  x=stack.Top();
                stack.pop();
                stack.push(!x);
            }
            else if(s[i]=='|')
            {
                int  x=stack.Top();
                stack.pop();
                int  y=stack.Top();
                stack.pop();
                stack.push(x||y);
            }
        }
        else if (s[i]=='<'&&s[i+1]=='-'&&s[i+2]=='>')
        {
            i+=2;
            int  x=stack.Top();
            stack.pop();
            int  y=stack.Top();
            stack.pop();
            if (x==y)
            {
                stack.push(1);
            }
            else
            {
                stack.push(0);
            }          

        }
        else if (s[i]=='-'&&s[i+1]=='>')
        {
            i+=1;
            int  x=stack.Top();
            stack.pop();
            int  y=stack.Top();
            stack.pop();
            if (x==0&&y==1)
            {
                stack.push(0);
            }
            else
            {
                stack.push(1);
            }
        }
        i++;
    }
    return stack.Top()==1?"TRUE":"FALSE";
}
// End of functions for logical expressions
