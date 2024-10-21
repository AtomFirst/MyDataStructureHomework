#include<iostream>
using namespace std;

using ll=long long;

void solve(){
    int g,y,r,n; cin>>r>>y>>g>>n;
    int c=g+y+r;
    ll time=0;
    // green -> yellow -> red
    for(int i=1;i<=n;i++){
        int k,t; cin>>k>>t;
        if(k==0) time+=t;
        else{
            int x;
            if(k==1) x=g+y+r;
            else if(k==2) x=g+y;
            else if(k==3) x=g;
            int lt=(x-t+time)%c;
            if(lt<=g);
            else time+=c-lt;
        }
        //cerr<<"time="<<time<<' ';
    }
    cout<<time<<'\n';
}

int main(){
    ios::sync_with_stdio(0),
        cin.tie(0),cout.tie(0);
    int t=1;
    //cin>>t;
    while(t--) solve();
    return 0;
}