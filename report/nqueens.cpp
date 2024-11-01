#include<iostream>
#include<cmath>
#include<stack>

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

void dfs(int i){
    if(i>=N){ // addr 0
        show(); // addr 1
        return;
    } 
    for(int j=0;j<N;j++) // addr 2
        if(valid(i,j)){
            line[i]=j;
            dfs(i+1);
        }
}

struct status{
    int i,j,pc;
};

void solve(){
    stack<status>s; s.push({0,-1,0});
    while(s.size()){
        auto &[i,j,pc]=s.top();
        switch(pc){
        case 0:
            if(i>=N) pc=1;
            else pc=2;
            break;
        case 1:
            show(); s.pop();
            break;
        case 2:
            for(++j;j<N;j++)
                if(valid(i,j)){
                    line[i]=j;
                    s.push({i+1,-1,0});
                    break;
                }
            if(j>=N)
                s.pop();
            break;
        default:
            cerr<<"invaild pc!";
            exit(-1);
        }
    }
}

int main(){
    //dfs(0);    
    solve();

    return 0;
}