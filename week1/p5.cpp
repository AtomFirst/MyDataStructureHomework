#include<iostream>
using namespace std;

using ll=long long;

void solve(){
    int res=0,lst=1;
    for(int x;cin>>x and x;res+=lst)
        if(x==1)
            lst=1;
        else{
            if(lst==1) lst=2;
            else lst+=2;
        }
    cout<<res<<'\n';
}

int main(){
    ios::sync_with_stdio(0),
        cin.tie(0),cout.tie(0);
    int t=1;
    //cin>>t;
    while(t--) solve();
    return 0;
}