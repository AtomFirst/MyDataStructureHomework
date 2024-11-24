#include<iostream>
using namespace std;

struct Node{
    Node(int data=0,Node *child=nullptr,Node *sibing=nullptr):data(data),child(child),sibing(sibing){}

    int data;
    Node *child,*sibing;
};

Node* create(istream &in){
    int n; 
    if(!(in>>n)) return nullptr;

    Node** nodes=new Node*[n+1];
    for(int i=1;i<=n;i++)
        nodes[i]=new Node(i);
    
    for(int i=1;i<=n;i++){
        int k; in>>k;
        if(k==0) continue;
        int ch; in>>ch;
        nodes[i]->child=nodes[ch];
        Node* lstsib=nodes[i]->child;
        for(int j=2;j<=k;j++)
            cin>>ch,
            lstsib->sibing=nodes[ch],
            lstsib=lstsib->sibing;
    }

    return nodes[1];
}

void TraverseLevelI(Node* tree,int i){
    if(i==1)
        for(;tree;tree=tree->sibing)
            cout<<tree->data<<" ";
    else
        for(;tree;tree=tree->sibing)
            TraverseLevelI(tree->child,i-1);
}

int main(){
    Node* tree=create(cin);
    int i; cin>>i;

    cout<<"Traverse level: ";
    TraverseLevelI(tree,i);
    cout<<endl;

    return 0;
}