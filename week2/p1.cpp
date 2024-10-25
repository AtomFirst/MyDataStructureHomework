#include "ADTList.cpp"

template<typename T>
void BubbleSort(T &list){
    for(auto i=list.end();i!=list.begin();--i)
        for(auto j=list.begin(),k=++(list.begin());k!=i;++j,++k)
            if(*j>*k)
                swap(*j,*k);
}

int main(){
    int n; cin>>n;
    SquList<int> list1(n);
    LinkList<int> list2;
    
    for(int i=0,x;i<n;i++){
        cin>>x;
        list2.push_back(x);
        list1.setElem(i,x);
    }

    cout<<"SeqList:"<<endl;
    BubbleSort(list1);
    cout<<"After sort(): "; list1.traverse();

    cout<<"LinkList:"<<endl;
    BubbleSort(list2);
    cout<<"After sort(): "; list2.traverse();

    return 0;
}