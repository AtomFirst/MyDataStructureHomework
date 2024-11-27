#include<iostream>
#include<vector>
#include<algorithm>
#include<array>

using namespace std;
using ll=long long;
using int2=array<int,2>;

#define all(x) x.begin(),x.end()

int grip[3][3];

bool win(int col){
    for(int i=0;i<3;i++){
        bool ok=1;
        for(int j=0;j<3;j++)
            if(grip[i][j]!=col)
                ok=0;
        if(ok) return true;
    }
    for(int i=0;i<3;i++){
        bool ok=1;
        for(int j=0;j<3;j++)
            if(grip[j][i]!=col)
                ok=0;
        if(ok) return true;
    }
    if(grip[0][0]==col&&grip[1][1]==col&&grip[2][2]==col) 
        return true;
    if(grip[0][2]==col&&grip[1][1]==col&&grip[2][0]==col) 
        return true;
    return false;
}

bool end(){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(grip[i][j]==0) return false;
    return true;
}

int cntn(int n){
    int cnt=0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(grip[i][j]==n) cnt++;
    return cnt;
};

int dfs(int first){
    if(win(first)) return cntn(0)+1;
    if(win(3-first)) return -cntn(0)-1;
    if(end()) return 0;

    int res=-10000;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            if(grip[i][j]!=0) continue;
            grip[i][j]=first;
            res=max(res,-dfs(3-first));
            grip[i][j]=0;
        }
    return res;
}

int solve(){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            cin>>grip[i][j];
    
    int c1=cntn(1),c2=cntn(2);
    return dfs(c1==c2?1:2);
}

int main(){
    ios::sync_with_stdio(0),
        cin.tie(0),cout.tie(0);

    int t=1;
    cin>>t;
    while(t--)
        cout<<solve()<<endl;

    return 0;
}