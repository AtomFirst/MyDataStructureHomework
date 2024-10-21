#include "ADTList.cpp"

template<typename T>
void unique(T *list){
    for(auto i=list->begin();i!=list->end();++i){
        auto j=i; ++j;
        while(j!=list->end()){
            //cerr<<(*i)<<" cmp "<<(*j)<<endl;
            if(*i==*j)
                j=list->erase(j);
            else
                ++j;
        }
    }
}

int main(){
    int n; cin>>n;
    SquList<int> *list1=new SquList<int>(n);
    LinkList<int> *list2=new LinkList<int>;
    
    for(int i=0,x;i<n;i++){
        cin>>x;
        list2->push_back(x);
        list1->setElem(i,x);
    }

    cout<<"SeqList:"<<endl;
    cout<<"Before unique(): "; list1->traverse();
    unique(list1);
    cout<<"After unique(): "; list1->traverse();

    cout<<"LinkList:"<<endl;
    cout<<"Before unique(): "; list2->traverse();
    unique(list2);
    cout<<"After unique(): "; list2->traverse();

    return 0;
}