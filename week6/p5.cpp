#include<iostream>
#include<set>
using namespace std;

int grip[20][10];

int main(){
    for(int i=14;i>=0;i--)
        for(int j=0;j<10;j++)
            cin>>grip[i][j];
    
    set<pair<int,int>>s,t;

    for(int i=3;i>=0;i--)
        for(int j=0,x;j<4;j++){
            cin>>x;
            if(x==1)
                s.insert({i,j});
        }
    
    int d; cin>>d;

    for(auto [y,x]:s)
        t.insert({y+15,x+d-1});
    
    int i=0; bool ok=0;
    while(1){
        for(auto [y,x]:t)
            if(y-(i+1)<0 || grip[y-(i+1)][x])
                ok=1;
        if(ok) break;
        ++i;
    }

    for(auto [y,x]:t)
        grip[y-i][x]=1;

    for(int i=14;i>=0;i--){
        for(int j=0;j<10;j++)
            cout<<grip[i][j]<<" ";
        cout<<endl;
    }

    return 0;
}