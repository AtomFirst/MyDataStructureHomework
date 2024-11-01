#include "ADTStack.cpp"
#include<iomanip>

int main(){
    int m; cin>>m;
    Stack<int>s;
    for(int i=1;i<=m;i++){
        cout<<"["<<setw(2)<<i<<"]: ";
        string opt; int x; cin>>opt;
        if(opt=="push") cin>>x;
        bool ok; int t=-1;
        if(opt=="clear"){
            s.clear();
            cout<<"CLEAR S\n";
        }else if(opt=="empty"){
            cout<<"S "<<(s.empty()?"is":"is't")<<" EMPTY\n";
        }else if(opt=="length"){
            cout<<"LENGTH OF S: "<<s.length()<<"\n";
        }else if(opt=="getTop"){
            ok=s.getTop(t);
            if(ok)
                cout<<"TOP OF S: "<<t<<"\n";
            else
                cout<<"S is empty, can't getTop!\n";
        }else if(opt=="traverse"){
            cout<<"S: ";
            s.traverse();
        }else if(opt=="push"){
            s.push(x);
            cout<<"PUSH "<<x<<"\n";
        }else if(opt=="pop"){
            ok=s.pop(t);
            if(ok)
                cout<<"POP "<<t<<"\n";
            else
                cout<<"S is empty, can't pop!\n";
        }else{
            cerr<<"INVAILD INPUT!\n";
            exit(-1);
        }   
    }

    return 0;
}