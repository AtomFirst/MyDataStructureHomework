#include<iostream>
#include<vector>
using namespace std;

// sort [begin,end)
template<typename T>
void QuickSort(T begin,T end){
    if(end-begin<=1) return;
    auto base=*begin;
    T l=begin,r=end; --r;
    while(l!=r){
        while(l!=r && *r>=base) --r;
        *l=*r;
        while(l!=r && *l<=base) ++l;
        *r=*l;
    }
    *l=base;

    QuickSort(begin,l);
    QuickSort(l+1,end);
}

int main(){
    int n; cin>>n;
    vector<int>a(n);
    for(auto &x:a) cin>>x;

    QuickSort(a.begin(),a.end());
    cout<<"QuickSort: ";
    for(auto x:a) cout<<x<<" ";
    cout<<endl;

    return 0;
}