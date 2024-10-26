#include<iostream>
#include<vector>
#include<array>

using namespace std;
using ll=long long;
using int2=array<int,2>;

int main(){
    int n; cin>>n;
    
    vector<int2>a(n);
    for(auto &[l,r]:a)
        cin>>l>>r;
    
    ll res=0;
    for(int i=0;i<n;i++){
        int l,r; cin>>l>>r;
        for(int j=0;j<n;j++)
            res+=max(0,min(r,a[j][1])-max(l,a[j][0]));
    }
    cout<<res<<'\n';

    return 0;
}