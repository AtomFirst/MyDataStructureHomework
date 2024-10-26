#include<iostream>
#include<vector>

using ll=long long;
using namespace std;

int main(){
    int n; cin>>n;
    vector<int>a(n),drop(n);
    for(int i=0;i<n;i++){
        int m; cin>>m>>a[i];
        for(int j=1;j<m;j++){
            int x; cin>>x;
            if(x>0)
                drop[i]+=a[i]-x,
                a[i]=x;
            else
                a[i]-=-x;
        }
    }

    ll sum=0,cnt=0,ec=0;

    for(int i=0;i<n;i++)
        sum+=a[i],
        cnt+=drop[i]>0?1:0;

    if(n>=3)
    for(int i=0;i<n;i++)
        ec+=(drop[i] and drop[(i+1)%n] and drop[(i+2)%n])?1:0;

    cout<<sum<<' '<<cnt<<' '<<ec<<'\n';

    return 0;
}