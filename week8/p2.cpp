#include<iostream>
#include<vector>
using namespace std;

// sort [begin,end)
template<typename T>
void BubbleSort(T begin,T end){
    for(;end-begin>1;--end)
        for(T i=begin,j=begin+1;j!=end;++i,++j)
            if(*i>*j)
                swap(*i,*j);
}

template<typename T>
void SelectSort(T begin,T end){
    for(;end-begin>1;++begin){
        T minp=begin;
        for(T i=begin+1;i!=end;++i)
            if(*minp>*i)
                minp=i;
        swap(*minp,*begin);
    }
}

template<typename T>
void MergeSort(T begin,T end){
    if(end-begin<=1) return;
    T mid=begin+(end-begin)/2;
    MergeSort(begin,mid);
    MergeSort(mid,end);
    
    auto tmp=*begin;
    vector<decltype(tmp)>buf1(begin,mid),buf2(mid,end);
    
    auto it1=buf1.begin(),it2=buf2.begin();
    for(;it1!=buf1.end() && it2!=buf2.end();++begin)
        if(*it1<*it2) *begin=*it1++;
        else *begin=*it2++;
    
    for(;it1!=buf1.end();++it1,++begin) *begin=*it1;
    for(;it2!=buf2.end();++it2,++begin) *begin=*it2;
}

int main(){
    int n; cin>>n;
    vector<int>a(n);
    for(auto &x:a) cin>>x;

    auto test1=a;
    BubbleSort(test1.begin(),test1.end());
    cout<<"BubbleSort: ";
    for(auto x:test1) cout<<x<<" ";
    cout<<endl;

    auto test2=a;
    SelectSort(test2.begin(),test2.end());
    cout<<"SelectSort: ";
    for(auto x:test2) cout<<x<<" ";
    cout<<endl;

    auto test3=a;
    MergeSort(test3.begin(),test3.end());
    cout<<"MergeSort: ";
    for(auto x:test3) cout<<x<<" ";
    cout<<endl;

    return 0;
}