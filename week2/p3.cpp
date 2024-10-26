#include "ADTList.cpp"

template<typename T>
void work(T &list,int m){
    auto cycle_next=[&](auto it){
        if(it==list.end())
            it=list.begin();
        ++it;
        if(it==list.end())
            it=list.begin();
        return it;
    };

    cout<<"out: ";
    for(auto it=list.begin();list.length();it=list.erase(it)){
        for(int i=1;i<m;i++)
            it=cycle_next(it);
        cout<<*it<<' ';
    }
    cout<<'\n';
}

int main(){
    int n,m; cin>>n>>m;
    SquList<int> list1(n);
    LinkList<int> list2;
    
    for(int i=1;i<=n;i++){
        int x=i;
        list2.push_back(x);
        list1.setElem(i-1,x);
    }

    cout<<"SeqList:"<<endl;
    work(list1,m);

    cout<<"LinkList:"<<endl;
    work(list2,m);

    return 0;
}