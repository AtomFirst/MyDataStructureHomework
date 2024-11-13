#ifndef _ADTBITREE
#define _ADTBITREE 1

#include<iostream>
#include<queue>
using namespace std;

typedef int status;
#define OK 1
#define ERROR 0
#define OVERFLOW -1

template<typename T>
struct BiNode{
    T data;
    BiNode *lchild,*rchild,*parent;

    BiNode(): lchild(nullptr),rchild(nullptr),parent(nullptr) {}
    BiNode(const T& data): data(data),lchild(nullptr),rchild(nullptr),parent(nullptr) {}
};

template<typename T>
class BiTree{
public:
    BiTree(BiNode<T>* root=nullptr): root(root) {}
    ~BiTree() {}
    // destroy
    void clear(){
        if(root){
            if(root->lchild)
                BiTree(root->lchild).clear();
            if(root->rchild)
                BiTree(root->rchild).clear();
            delete root;
            root=nullptr;
        }
    }
    template<typename U>
    BiNode<T>* create(U&& in){
        char cur;
        if(not (in>>cur) or cur=='#') return root=nullptr;
        root=new BiNode<T>(cur);
        root->lchild=BiTree().create(forward<U>(in));
        if(root->lchild)
            root->lchild->parent=root;
        root->rchild=BiTree().create(forward<U>(in));
        if(root->rchild)
            root->rchild->parent=root;
        return root;
    }
    bool empty(){
        return not root;
    }
    int depth(){
        if(empty()) return 0;
        return 1+max(BiTree(root->lchild).depth(),BiTree(root->rchild).depth());
    }
    T& getRoot(){
        return value(root);
    }
    T& value(BiNode<T>* p){
        return p->data;
    }
    BiNode<T>* parent(BiNode<T>* p){
        return p->parent;
    }
    BiNode<T>* leftChild(BiNode<T>* p){
        return p->lchild;
    }
    BiNode<T>* rightChild(BiNode<T>* p){
        return p->rchild;
    }
    BiNode<T>* leftBrother(BiNode<T>* p){
        if(not p->parent) return nullptr;
        if(p->parent->rchild!=p) return nullptr;
        return p->parent->lchild;
    }
    BiNode<T>* rightBrother(BiNode<T>* p){
        if(not p->parent) return nullptr;
        if(p->parent->lchild!=p) return nullptr;
        return p->parent->rchild;
    }
    void preOrderTraverse(auto&& worker){
        if(not root) return;
        worker(root->data);
        BiTree(root->lchild).preOrderTraverse(worker);
        BiTree(root->rchild).preOrderTraverse(worker);
    }
    void inOrderTraverse(auto&& worker){
        if(not root) return;
        BiTree(root->lchild).inOrderTraverse(worker);
        worker(root->data);
        BiTree(root->rchild).inOrderTraverse(worker);
    }
    void postOrderTraverse(auto&& worker){
        if(not root) return;
        BiTree(root->lchild).postOrderTraverse(worker);
        BiTree(root->rchild).postOrderTraverse(worker);
        worker(root->data);
    }
    void levelOrderTraverse(auto&& worker){
        if(not root) return;
        queue<BiNode<T>*>q; q.push(root);
        while(q.size()){
            BiNode<T>* cur=q.front(); q.pop();
            worker(cur->data);
            if(cur->lchild) q.push(cur->lchild);
            if(cur->rchild) q.push(cur->rchild);
        }
    }
    void assign(BiNode<T>* p,const T &data){
        p->data=data;
    }
    void insert(BiNode<T>* p,int lr,const T& data){
        if(lr==0)
            p->lchild=new BiNode<T>(data);
        else
            p->rchild=new BiNode<T>(data);
    }
    void erase(BiNode<T>* p,int lr){
        if(lr==0){
            BiTree(p->lchild).clear();
            p->lchild=nullptr;
        }else{
            BiTree(p->rchild).clear();
            p->rchild=nullptr;
        }
    }
//private:
    BiNode<T>* root;
};

#endif