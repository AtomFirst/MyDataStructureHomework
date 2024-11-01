#ifndef _ADTQUEUE
#define _ADTQUEUE 1

#include "ADTList.cpp"

template<typename T>
class Queue{
public:
    Queue(){}
    ~Queue(){}
    void clear(){
        elem.clear();
    }
    bool empty(){
        return elem.empty();
    }
    int length(){
        return elem.length();
    }
    status getHead(T &e){
        if(not length()) return ERROR;
        e=*elem.begin();
        return OK;
    }
    void traverse(){
        elem.traverse();
    }
    void push(T e){
        elem.insert(elem.end(),e);
    }
    status pop(T &e){
        if(not length()) return ERROR;
        e=*elem.begin();
        elem.erase(elem.begin());
        return OK;
    }

private:
    LinkList<T>elem;
};

#endif