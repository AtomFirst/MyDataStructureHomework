#include<iostream>
#include<vector>
#include<algorithm>

using ll=long long;
using namespace std;

int main(){
    int n; cin>>n;
    vector<int>a(n);
    for(int &x:a) cin>>x;
    sort(a.begin(),a.end());
    int res=1e9;
    for(int i=1;i<n;i++)
        res=min(res,a[i]-a[i-1]);
    cout<<res<<endl;

    return 0;
}