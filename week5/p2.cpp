#include "ADTBiTree.cpp"
#include<stack>

template<typename T>
void Traverse(const BiTree<T>& b,const char order[],auto &&worker){
    cout<<"Traverse(Order: "<<order<<"): ";

    stack<pair<BiNode<T>*,int>>s; s.emplace(b.root,0);
    while(s.size()){
        auto [x,i]=s.top(); s.pop();
        if(i+1<3) s.emplace(x,i+1);
        switch(order[i]){
        case 'L':
            if(x->lchild)
                s.emplace(x->lchild,0);
            break;
        case 'R':
            if(x->rchild)
                s.emplace(x->rchild,0);
            break;
        case 'r':
            worker(x->data);
            break;
        default:
            cerr<<"invaild order!";
            exit(-1);
        }
    }

    cout<<endl;
}

int main(){
    BiTree<char> b;
    b.create(cin);
    cout<<"b is created by in2.txt"<<endl<<endl;

    auto print=[](auto e){cout<<e<<" ";};

    cout<<"PreOrderTraverse(recursion): ";
    b.preOrderTraverse(print);
    cout<<endl;
    Traverse(b,"rLR",print);
    cout<<endl;

    cout<<"InOrderTraverse(recursion): ";
    b.inOrderTraverse(print);
    cout<<endl;
    Traverse(b,"LrR",print);
    cout<<endl;

    cout<<"PostOrderTraverse(recursion): ";
    b.postOrderTraverse(print);
    cout<<endl;
    Traverse(b,"LRr",print);
    cout<<endl;

    cout<<"LevelOrderTraverse(b): ";
    b.levelOrderTraverse(print);
    cout<<endl;

    return 0;
}