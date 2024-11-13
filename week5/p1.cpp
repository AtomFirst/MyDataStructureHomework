#include "ADTBiTree.cpp"
#include<sstream>

int main(){
    BiTree<char> b;
    b.create(istringstream("ABD#G###CE##F##"));
    cout<<"b is created by \"ABD#G###CE##F##\""<<endl;
    
    cout<<"depth(b)="<<b.depth()<<endl;

    cout<<"root(b): "<<b.getRoot()<<endl;

    cout<<"LeftChild of A: "<<b.leftChild(b.root)->data<<endl;

    cout<<"RightBrother of B: "<<b.rightBrother(b.root->lchild)->data<<endl;

    cout<<"InOrderTraverse(b): ";
    b.inOrderTraverse([](auto e){cout<<e<<' ';});
    cout<<endl;

    cout<<"assign 'H' to root"<<endl;
    b.assign(b.root,'H');

    cout<<"erase left child of root"<<endl;
    b.erase(b.root,0);

    cout<<"LevelOrderTraverse(b): ";
    b.levelOrderTraverse([](auto e){cout<<e<<' ';});
    cout<<endl;

    b.clear();
    cout<<"b is cleared"<<endl<<"b is empty: "<<b.empty()<<endl;
    return 0;
}