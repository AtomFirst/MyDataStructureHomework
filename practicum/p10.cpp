#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<map>
#include<sstream>
#include<iomanip>

using namespace std;

using ll=long long;

struct Token{
    ~Token(){}

    enum{NUM,OPT,VAR,ERR} type;
    
    double num;
    char opt; 
    string var; // also err
};

istream& operator>>(istream& in,Token& t){
    char ch;
    while(in.get(ch) && ch==' ');
    if(!in) return in; 

    // Number
    if(isdigit(ch) || ch=='.'){
        t.type=Token::NUM;
        bool point=(ch=='.');
        t.num=point?0:ch-'0';
        double a=point?1:10,
            b=point?0.1:1;
        
        while(in.get(ch)){
            if(isdigit(ch)){
                t.num=t.num*a+(ch-'0')*b;
                if(point) b*=0.1;
            }
            else if(ch=='.'){
                if(!point)
                    point=true,a=1,b=0.1;
                else{
                    t.type=Token::ERR;
                    t.var="More than one . in Number!";
                    break;
                }
            }
            else{
                in.unget();
                break;
            }
        }
        in.clear();
    }
    // Operator
    else if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^' || ch=='(' || ch==')' || ch=='='){
        t.type=Token::OPT;
        t.opt=ch;
    }
    // Variable
    else if(isalpha(ch) || ch=='_'){
        t.type=Token::VAR;
        t.var=ch;
        while(in.get(ch)){
            if(isalpha(ch) || isdigit(ch) || ch=='_')
                t.var.append(1,ch);
            else{
                if(ch!=' ')
                    in.unget();
                break;
            }
        }
        in.clear();

        if(t.var=="EXIT"){
            t.type=Token::ERR;
            t.var="'EXIT' should not be a variable name!";
        }
    }
    // Error
    else{
        t.type=Token::ERR;
        t.var="Invalid character '"+string(1,ch)+"' !";
    }

    return in;
}

ostream& operator<<(ostream& out,const Token& t){
    switch(t.type){
        case Token::NUM: return out<<"NUM("<<setprecision(15)<<t.num<<")";
        case Token::OPT: return out<<"OPT("<<t.opt<<")";
        case Token::VAR: return out<<"VAR("<<t.var<<")";
        case Token::ERR: return out<<"ERR("<<t.var<<")";
        default: return out<<"<<(Token): type error!";
    }
}

map<char,int> priority{
    {'^',4},
    {'*',3},{'/',3},
    {'+',2},{'-',2},
    {'=',1},
    {'(',0},{')',0}
};

bool geq(char opt_a,char opt_b){
    return priority[opt_a]>=priority[opt_b];
}

double calc(char opt,double a,double b){
    switch(opt){
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
        case '^': return pow(a,b);
        case '=': return b;
        default: cerr<<"calc(,,): invaild opt '"<<opt<<"' !"; return a;
    }
}

class Interpreter{
public:
    bool operator()(const string& input,ostream& out){
        // scanner
        vector<Token>tokens{Token{.type=Token::OPT,.opt='('}};
        istringstream stream(input);

        for(Token t;stream>>t;){
            if(t.type==Token::ERR){
                cerr<<"scanner: column "<<stream.tellg()<<": error: "<<t.var<<endl;
                return false;
            }
            
            tokens.emplace_back(t);
        }

        tokens.push_back(Token{.type=Token::OPT,.opt=')'});

        auto ScannerOutput=[&](ostream& out){
            out<<"Scanner:\n    ";
            for(int i=1;i+1<tokens.size();i++)
                out<<tokens[i]<<' ';
            out<<endl;
        };
        ScannerOutput(out);

        // parser
        vector<double>val_stack;
        vector<int>id_stack;
        vector<char>opt_stack;

        auto StackOutput=[&](ostream& out,char opt){
            out<<"--> ";
            out<<"value: ";
            for(auto x:val_stack)
                out<<x<<" ";
            out<<"\n    operator: ";
            for(auto x:opt_stack) 
                out<<x<<" ";
            out<<"{"<<opt<<"}";
            out<<"\n";
        };

        cout<<"Parser:\n";

        for(int i=0;const auto &t:tokens){
            bool bracket=(t.opt==')'),
                stk=false;
            switch(t.type){
                case Token::NUM: 
                    val_stack.emplace_back(t.num);
                    id_stack.emplace_back(i);
                    break;
                
                case Token::VAR:
                    val_stack.emplace_back(vars[t.var]);
                    id_stack.emplace_back(i);
                    break;
                
                case Token::OPT:
                    if(t.opt=='('){
                        opt_stack.emplace_back(t.opt);
                        break;
                    }

                    while(opt_stack.size() && geq(opt_stack.back(),t.opt)){
                        if(opt_stack.back()!='(')
                            StackOutput(out,t.opt),stk=true;

                        char opt=opt_stack.back(); opt_stack.pop_back();

                        if(opt=='(') break;

                        if(val_stack.size()<2){
                            cerr<<"parser: error: too many operator!\n";
                            return false;
                        }

                        double b=val_stack.back(); val_stack.pop_back();
                        double a=val_stack.back(); val_stack.pop_back();
                        id_stack.pop_back(); 
                        int id=id_stack.back(); id_stack.pop_back();
                        
                        double c=calc(opt,a,b);
                        val_stack.emplace_back(c);
                        id_stack.emplace_back(-1);
                        
                        if(opt=='='){
                            if(id==-1){
                                cerr<<"parser : error: cannot assign a lvalue!\n";
                                return false;
                            }
                            if(tokens[id].type!=Token::VAR){
                                cerr<<"parser: "<<"token "<<id<<" : "<<tokens[id]<<" : error: cannot assign a lvalue!\n";
                                return false;
                            }
                            vars[tokens[id].var]=c;
                        }
                    }
                    
                    if(!bracket)
                        opt_stack.emplace_back(t.opt);
                    
                    if(stk)
                        StackOutput(out,' ');

                    break;

                default: 
                    cerr<<"parser: "<<"token "<<i<<" : error: invaild token!\n";
                    return false;
            }

            ++i;
        }

        if(val_stack.size()==0);
        else if(val_stack.size()==1){
            vars["_"]=val_stack.back();
            out<<setprecision(15)<<vars["_"]<<endl;
        }
        else{
            cerr<<"parser: error: too many number!\n";
        }

        return true;
    }

private:
    map<string,double>vars;
};

const char hint[]="\
Calculater 1.0\n\n\
Support decimal number and variable.\n\
Support a+b a-b a*b a/b a^b(power) a=b(assign).\n\
Input formula to calculate.\n\
Input 'EXIT' to exit this program.\n\
---\n\
";

void Interactive(){
    cout<<hint;

    Interpreter interpreter;

    char buffer[0x100];
    while(true){
        cout<<"> ";
        cin.getline(buffer,0xff,'\n');
        if(string(buffer)=="EXIT") break;

        interpreter(buffer,cout);
    }
}

int main(){
    Interactive();

    return 0;
}