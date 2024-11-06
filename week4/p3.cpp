#include<iostream>
#include<vector>

using ll=long long;
using namespace std;

int main(){
    int n,k,t,x1,y1,x2,y2; 
    cin>>n>>k>>t>>x1>>y1>>x2>>y2;
    int cnt1=0,cnt2=0;
    for(int i=1;i<=n;i++){
        int lx=0; bool first1=1,first2=1;
        for(int j=1;j<=t;j++){
            int x,y; cin>>x>>y;
            if(x1<=x and x<=x2 and y1<=y and y<=y2){
                if(first1) first1=0,++cnt1;
                if(first2 and ++lx>=k) first2=0,++cnt2;
            }else
                lx=0;
        }
    }
    cout<<cnt1<<endl<<cnt2<<endl;
    return 0;
}