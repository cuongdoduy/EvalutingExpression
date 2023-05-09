#include<EvalutingExpression.h>
int main(int argc, char ** argv)
{
    string file_input(argv[1]);
    string s,value;
    ifstream ReadFile(file_input);
    getline(ReadFile,s);  
    getline(ReadFile,value);
    cout<<LogicPostfixPrefixCalculator(s,value)<<endl;
    return 0;
}