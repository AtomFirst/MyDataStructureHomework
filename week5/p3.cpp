#include "ADTBiTree.cpp"

template<typename T>
bool DeleteValXChild(BiTree<T>& b,const T &x){
    if(not b.root) return 0;
    if(b.getRoot()==x){
        b.clear();
        return 1;
    }
    auto lt=BiTree<T>(b.root->lchild);
    if(DeleteValXChild(lt,x)) b.root->lchild=nullptr;
    auto rt=BiTree<T>(b.root->rchild);
    if(DeleteValXChild(rt,x)) b.root->rchild=nullptr;
    return 0;
}

int main(){
    BiTree<char> b;
    b.create(cin);
    cout<<"b is created by in3.txt"<<endl<<endl;

    auto print=[](auto e){cout<<e<<" ";};

    cout<<"PreOrderTraverse(b): ";
    b.preOrderTraverse(print);
    cout<<endl;

    DeleteValXChild(b,'6');
    cout<<"delete 6"<<endl;

    cout<<"PreOrderTraverse(b): ";
    b.preOrderTraverse(print);
    cout<<endl;

    return 0;
}