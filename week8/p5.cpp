#include<iostream>
#include<set>
#include<array>
using namespace std;

using int2=array<int,2>;

int dx[]{-1,1,0,0,-1,-1,1,1},dy[]{0,0,-1,1,-1,1,-1,1};

int main(){
    int n; cin>>n;
    set<int2>s;
    for(int i=0;i<n;i++){
        int x,y; cin>>x>>y;
        s.insert({x,y});
    }
    int res[5]{0};
    for(auto [x,y]:s){
        bool ok=1;
        for(int i=0;i<4;i++)
            if(s.count({x+dx[i],y+dy[i]})==0)
                ok=0;
        if(!ok) continue;
        int cnt=0;
        for(int i=4;i<8;i++)
            if(s.count({x+dx[i],y+dy[i]}))
                ++cnt;
        ++res[cnt];
    }
    for(auto x:res)
        cout<<x<<endl;
    return 0;
}