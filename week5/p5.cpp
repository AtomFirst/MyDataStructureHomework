#include<iostream>
using namespace std;

bool jumping(int n){
    if(n%7==0) return true;
    for(;n;n/=10)
        if(n%10==7)
            return true;
    return false;
}

int main(){
    int n; cin>>n;
    int cnt[]{0,0,0,0};
    for(int i=0,j=1;n>0;i=(i+1)%4,++j)
        if(jumping(j)) ++cnt[i];
        else --n;
    for(int x:cnt)
        cout<<x<<endl;
    return 0;
}