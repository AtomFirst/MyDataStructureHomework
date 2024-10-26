#ifndef _ADTLIST
#define _ADTLIST 1

#include<iostream>
#include<stdlib.h>
using namespace std;

typedef int status;
#define OK 1
#define ERROR 0
#define OVERFLOW -1

// 下标从0开始（与书上不同）
template<typename T>
class SquList{
public:
    SquList(int len=0,T elem=T()): size(len),capacity(max(16,len)){
        head=new T[capacity];
        if(head==nullptr)
            exit(OVERFLOW);
        for(int i=0;i<size;++i)
            head[i]=elem;
    }
    ~SquList(){
        delete [] head;
    }
    void clear(){
        size=0;
    }
    bool empty(){
        return size==0;
    }
    int length(){
        return size;
    }
    status reserve(int n_capacity){
        capacity=n_capacity;
        head=(T*)realloc(head,sizeof(T)*capacity);
        if(head==nullptr)
            return OVERFLOW;
        return OK;
    }
    status resize(int n_size){
        size=n_size;
        if(size>capacity)
            return reserve(capacity<<1);
        return OK;
    }
    status getElem(int i,T &e){
        if(i<0 or i>=size) return ERROR;
        e=head[i];
        return OK;
    }
    int locateElem(T e){
        for(int i=0;i<size;++i)
            if(head[i]==e)
                return i;
        return -1;
    }
    status priorElem(T cur_e,T &pre_e){
        int i=locateElem(cur_e);
        if(i==-1 or i-1<0) return ERROR;
        pre_e=head[i-1];
        return OK;
    }
    status nextElem(T cur_e,T &next_e){
        int i=locateElem(cur_e);
        if(i==-1 or i+1<size) return ERROR;
        next_e=head[i+1];
        return OK;
    }
    void traverse(){
        for(int i=0;i<size;++i)
            cout<<head[i]<<" ";
        cout<<endl;
    }
    status setElem(int i,T &e){
        if(i<0 or i>=size) return ERROR;
        T tmp=head[i]; head[i]=e; e=tmp;
        return OK;
    }
    status insertElem(int i,T e){
        if(i<0 or i>size) return ERROR;
        if(status s=resize(size+1);s)
            return s;
        for(int j=size-1;j>=i;--j)
            head[j+1]=head[j];
        ++size; head[i]=e;
        return OK;
    }
    status deleteElem(int i,T &e){
        if(i<0 or i>=size) return ERROR;
        e=head[i];
        for(int j=i+1;j<size;j++)
            head[j-1]=head[j];
        --size;
        return OK;
    }

    // methods with iterator
    class iterator{
    public:
        iterator(T *p): p(p) {}
        T &operator*(){
            return *p;
        }
        bool operator!=(const iterator &b)const{
            return p!=b.p;
        }
        bool operator==(const iterator &b)const{
            return p==b.p;
        }
        iterator &operator++(){
            ++p;
            return *this;
        }
        iterator &operator--(){
            --p;
            return *this;
        }
        iterator operator+(int d)const{
            return iterator(p+d);
        }
        iterator operator-(int d)const{
            return iterator(p-d);
        }
        int operator-(const iterator &b)const{
            return p-b.p;
        }
    private:
        T *p;
    };
    iterator begin(){
        return iterator(head);
    }
    iterator end(){
        return iterator(head+size);
    }
    iterator find(T e){
        iterator it=begin();
        while(it!=end() and *it!=e) ++it;
        return it;
    }
    iterator insert(iterator it,T e){
        int i=it-begin();
        if(resize(size+1)!=OK)
            return end();
        for(int j=size-1;j>i;j--)
            head[j]=head[j-1];
        head[i]=e;
        return iterator(head+i);
    }
    iterator erase(iterator it){
        iterator cur=it,nxt=it; ++nxt;
        for(;nxt!=end();++cur,++nxt)
            *cur=*nxt;
        --size;
        return it;
    }

private:
    T *head;
    int size,capacity;
};

template<typename T>
class LinkList{
public:
    LinkList(): size(0){
        head=new Node();
        head->nxt=head->pre=head;
    }
    ~LinkList(){
        clear();
    }
    void clear(){
        size=0;
        for(Node *p;p=head->nxt,p!=head;){
            head->nxt=p->nxt;
            head->nxt->pre=head;
            delete p;
        }
    }
    bool empty(){
        return size==0;
    }
    int length(){
        return size;
    }
    status getElem(int i,T &e){
        if(i<0 or i>=size) return ERROR;
        Node *p=head->nxt;
        for(int j=0;j<i;j++)
            p=p->nxt;
        e=p->elem;
        return OK;
    }
    int locateElem(T e){
        int i=0;
        for(Node *p=head->nxt;p!=head;p=p->nxt,++i)
            if(p->elem==e)
                return i;
        return -1;
    }
    status priorElem(T cur_e,T &pre_e){
        for(Node *p=head->nxt,*q=p->nxt;q!=head;p=p->nxt,q=q->nxt)
            if(q->elem==cur_e){
                pre_e=p->elem;
                return OK;
            }
        return ERROR;
    }
    status nextElem(T cur_e,T &next_e){
        for(Node *p=head->nxt,*q=p->nxt;q!=head;p=p->nxt,q=q->nxt)
            if(p->elem==cur_e){
                next_e=q->elem;
                return OK;
            }
        return ERROR;
    }
    void traverse(){
        for(Node *p=head->nxt;p!=head;p=p->nxt)
            cout<<(p->elem)<<" \n"[p->nxt==head];
    }
    status setElem(int i,T &e){
        int j=0;
        for(Node *p=head->nxt;p!=head;p=p->nxt,++j)
            if(j==i){
                T tmp=p->elem;
                p->elem=e;
                e=tmp;
                return OK;
            }
        return ERROR;
    }
    status insertElem(int i,T e){
        int j=0;
        for(Node *p=head,*q=p->nxt;j==0 || p!=head;p=p->nxt,q=q->nxt,++j)
            if(j==i){
                Node *cur=new Node(e);
                cur->nxt=q; cur->pre=p;
                p->nxt=cur; q->pre=cur;
                ++size;
                return OK;
            }
        return ERROR;
    }
    status deleteElem(int i,T &e){
        int j=0;
        for(Node *p=head,*q=p->nxt;q!=head;p=p->nxt,q=q->nxt,++j)
            if(j==i){
                e=q->elem;
                p->nxt=q->nxt;
                p->nxt->pre=p;
                delete q;
                --size;
                return OK;
            }
        return ERROR;
    }

    struct Node{
        Node(T e=T()): 
            elem(e),pre(nullptr),nxt(nullptr) {}
        Node *pre,*nxt;
        T elem;
    };

    class iterator{
    public:
        iterator(Node *p): p(p) {}
        T &operator*(){
            return p->elem;
        }
        bool operator!=(const iterator &b)const{
            return p!=b.p;
        }
        bool operator==(const iterator &b)const{
            return p==b.p;
        }
        iterator &operator++(){
            p=p->nxt;
            return *this;
        }
        iterator &operator--(){
            p=p->pre;
            return *this;
        }
        Node *getNode(){
            return p;
        }
    private:
        Node *p;
    };
    iterator begin(){
        return iterator(head->nxt);
    }
    iterator end(){
        return iterator(head);
    }
    iterator find(T e){
        iterator it=begin();
        while(it!=end() and *it!=e) ++it;
        return it;
    }
    iterator insert(iterator it,T e){
        Node *q=it.getNode(),*p=q->pre,*cur=new Node(e);
        cur->nxt=q; cur->pre=p;
        p->nxt=cur; q->pre=cur;
        ++size;
        return iterator(cur);
    }
    iterator erase(iterator it){
        Node *cur=it.getNode(),*p=cur->pre,*q=cur->nxt;
        delete cur;
        p->nxt=q; q->pre=p;
        --size;
        return iterator(q);
    }
    iterator push_back(T e){
        return insert(end(),e);
    }
    
private:
    Node *head;
    int size;
};

#endif