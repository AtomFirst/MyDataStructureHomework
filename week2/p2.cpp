#include "ADTList.cpp"

template<typename T>
void Union(T &a,T &b){
    auto j=b.begin();
    for(auto i=a.begin();i!=a.end();++i)
        for(;j!=b.end() and *i<=*j;++j)
            if(*i<*j)
                i=a.insert(i,*j);
    for(;j!=b.end();++j)
        a.insert(a.end(),*j);
}

int main(){
    int a; cin>>a;
    SquList<int> list11(a);
    LinkList<int> list21;
    
    for(int i=0,x;i<a;i++){
        cin>>x;
        list21.push_back(x);
        list11.setElem(i,x);
    }

    int b; cin>>b;
    SquList<int> list12(b);
    LinkList<int> list22;
    
    for(int i=0,x;i<b;i++){
        cin>>x;
        list22.push_back(x);
        list12.setElem(i,x);
    }

    cout<<"SeqList:"<<endl;
    Union(list11,list12);
    cout<<"After merge(): "; list11.traverse();

    cout<<"LinkList:"<<endl;
    Union(list21,list22);
    cout<<"After merge(): "; list21.traverse();

    return 0;
}