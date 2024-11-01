#include<iostream>
#include<sstream>
#include<stack>

using namespace std;

template<typename T>
struct BiNode{
    T elem; BiNode *lson,*rson;
    BiNode(const T &elem): elem(elem),lson(nullptr),rson(nullptr) {}
};

template<typename T>
BiNode<char>* create(T&& in){
    char cur;
    if(not (in>>cur) or cur=='#'){
        return nullptr;
    }

    BiNode<char>* rt=new BiNode<char>(cur);
    rt->lson=create(forward<T>(in));
    rt->rson=create(forward<T>(in));
    return rt;
}

template<typename T>
void PreOrderTraverse(BiNode<T>* rt){
    cout<<(rt->elem)<<" "; // addr 0
    if(rt->lson) PreOrderTraverse(rt->lson); // addr 1
    if(rt->rson) PreOrderTraverse(rt->rson); // addr 2
}

template<typename T>
void Traverse(BiNode<T>* rt,const char order[]){
    cout<<"Traverse(Order: "<<order<<"): ";

    stack<pair<BiNode<T>*,int>>s; s.emplace(rt,0);
    while(s.size()){
        auto [x,i]=s.top(); s.pop();
        if(i+1<3) s.emplace(x,i+1);
        switch(order[i]){
        case 'L':
            if(x->lson)
                s.emplace(x->lson,0);
            break;
        case 'R':
            if(x->rson)
                s.emplace(x->rson,0);
            break;
        case 'r':
            cout<<(x->elem)<<" ";
            break;
        default:
            cerr<<"invaild order!";
            exit(-1);
        }
    }

    cout<<endl;
}

int main(){
    BiNode<char> *rt=create(istringstream("ABD#G###CE##F##"));

    Traverse(rt,"rLR");
    Traverse(rt,"LrR");
    Traverse(rt,"LRr");

    return 0;
}