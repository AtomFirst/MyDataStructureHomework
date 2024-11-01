#include "ADTStack.cpp"
#include<cmath>

using namespace std;

const int N=8;

int line[N];

int tot;
void show(){
    cout<<"No. "<<(++tot)<<":\n";
    for(int i=0;i<N;i++) for(int j=0;j<N;j++)
        cout<<"+@"[line[i]==j]<<" \n"[j==N-1];
    cout<<endl;
}

bool valid(int i,int j){
    for(int k=0;k<i;k++)
        if(line[k]==j or abs(line[k]-j)==i-k)
            return false;
    return true;
}

struct stack_status{
    int i,j,pc;
};

void solve(){
    Stack<stack_status>s; s.push({0,-1,0});
    while(s.length()){
        stack_status tmp; s.pop(tmp);
        auto &[i,j,pc]=tmp;
        switch(pc){
        case 0:
            if(i>=N) pc=1;
            else pc=2;
            s.push(tmp);
            break;
        case 1:
            show(); 
            break;
        case 2:
            for(++j;j<N;j++)
                if(valid(i,j)){
                    line[i]=j;
                    s.push(tmp);
                    s.push({i+1,-1,0});
                    break;
                }
            break;
        default:
            cerr<<"invaild pc!";
            exit(-1);
        }
    }
}

int main(){    
    solve();

    return 0;
}