#include "ADTList.cpp"

// 顺序表实现
template<typename T>
void reverse_SquList(SquList<T> *list){
    for(auto l=list->begin(),r=list->end()-1;r-l>0;++l,--r)
        swap(*l,*r);
}

// 双向循环链表实现
template<typename T>
void reverse_LinkList(LinkList<T> *list){
    auto cur=list->end().getNode();
    do{
        swap(cur->pre,cur->nxt);
        cur=cur->pre;
    }while(cur!=list->end().getNode());
}

// 单链表实现
template<typename T>
struct Node{
    T elem;
    Node *nxt;
    Node(T elem=T()):elem(elem),nxt(nullptr) {}
};

template<typename T>
Node<T> *insert(Node<T> *cur,T elem){
    Node<T> *now=new Node<T>(elem);
    now->nxt=cur->nxt;
    cur->nxt=now;
    return now;
}

template<typename T>
void traverse(Node<T> *head){
    head=head->nxt;
    while(head!=nullptr)
        cout<<(head->elem)<<' ',
        head=head->nxt;
    cout<<'\n';
}

template<typename T>
void reverse_LinkList(Node<T> *head){
    Node<T> *p=head->nxt,*q;
    head->nxt=nullptr;
    for(;p!=nullptr;p=q){
        q=p->nxt;
        p->nxt=head->nxt;
        head->nxt=p;
    }
}

int main(){
    int n; cin>>n;
    SquList<int> *list1=new SquList<int>(n);
    LinkList<int> *list2=new LinkList<int>;
    Node<int> *list3=new Node<int>,*rear=list3;
    for(int i=0,x;i<n;i++){
        cin>>x;
        list2->push_back(x);
        rear=insert(rear,x);
        list1->setElem(i,x);
    }

    cout<<"SeqList:"<<endl;
    cout<<"Before reverse(): "; list1->traverse();
    reverse_SquList(list1);
    cout<<"After reverse(): "; list1->traverse();

    cout<<"LinkList:"<<endl;
    cout<<"Before reverse(): "; list2->traverse();
    reverse_LinkList(list2);
    cout<<"After reverse(): "; list2->traverse();

    cout<<"LinkList:"<<endl;
    cout<<"Before reverse(): "; traverse(list3);
    reverse_LinkList(list3);
    cout<<"After reverse(): "; traverse(list3);

    return 0;
}