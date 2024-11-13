#include "ADTBiTree.cpp"
#include<tuple>

template<typename T>
tuple<int,int,bool> _IsComplete(BiNode<T>* b){
    if(not b) return {-1,-1,true};
    auto [ll,lr,lb]=_IsComplete(b->lchild);
    auto [rl,rr,rb]=_IsComplete(b->rchild);
    if(lb and rb and lr>=rl and ll-rr<=1)
        return {1+ll,1+rr,true};
    return {-1,-1,false};
}

template<typename T>
bool IsComplete(BiTree<T> b){
    auto [ld,rd,flag]=_IsComplete(b.root);
    return flag;
}

int main(){
    BiTree<char> b;
    b.create(cin);
    cout<<"b is created by in4.txt"<<endl<<endl;

    auto print=[](auto e){cout<<e<<" ";};

    cout<<"LevelOrderTraverse(b): ";
    b.levelOrderTraverse([](auto e){cout<<e<<' ';});
    cout<<endl;

    cout<<"b is complete binary tree: "<<IsComplete(b)<<endl;

    return 0;
}