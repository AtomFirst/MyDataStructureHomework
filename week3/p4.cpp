#include<iostream>
#include<vector>

using ll=long long;
using namespace std;

int main(){
    int n,k; cin>>n>>k;
    int res=0,sum=0;
    for(int i=1,x;i<=n;i++){
        cin>>x; sum+=x;
        if(sum>=k)
            ++res,sum=0;
    }
    if(sum>0) ++res,sum=0;
    cout<<res<<endl;

    return 0;
}