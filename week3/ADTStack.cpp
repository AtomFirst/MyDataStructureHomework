#ifndef _ADTSTACK
#define _ADTSTACK 1

#include "ADTList.cpp"

template<typename T>
class Stack{
public:
    Stack(){}
    ~Stack(){}
    void clear(){
        elem.clear();
    }
    bool empty(){
        return elem.empty();
    }
    int length(){
        return elem.length();
    }
    status getTop(T &e){
        if(not length()) return ERROR;
        e=*--elem.end();
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
        e=*--elem.end();
        elem.erase(--elem.end());
        return OK;
    }

private:
    SquList<T>elem;
};

#endif