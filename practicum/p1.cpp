#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

using namespace std;

template<typename T>
struct SLinkNode{
    SLinkNode(): next(nullptr) {}
    SLinkNode(const T& elem): elem(elem),next(nullptr) {}

    T elem;
    SLinkNode* next;
};

struct process{
    friend ostream& operator<<(ostream& out,const process& p){
        return out<<"PID: "<<p.pid<<", NAME: "<<p.name<<", MEM(K):"<<p.mem;
    }

    int pid;
    string name;
    int mem;
};

SLinkNode<process>* GetProcess(){
    SLinkNode<process>* res=nullptr;

#if defined(__linux__)
    const char cmd[]="ps aux > system_process_data.txt";
#elif defined(_WIN32)
    const char cmd[]="tasklist /FO CSV /NH > system_process_data.txt";
#endif

    if(system(cmd)){
        cerr<<"Fail to get process!\n";
        return nullptr;
    }

    ifstream fin("system_process_data.txt",ios::in);

    if(!fin.is_open()){
        cerr<<"Fail to open system_process_data.txt!\n";
        return nullptr;
    }

    char buf[0x100];

#if defined(__linux__)
    fin.getline(buf,0xff,'\n');
    for(process p;fin>>buf>>p.pid>>buf>>buf>>buf>>p.mem>>buf>>buf>>buf>>buf>>p.name;fin.getline(buf,0xff,'\n')){
        auto cur=new SLinkNode<process>(p);
        cur->next=res; res=cur;
    }
#elif defined(_WIN32)
    
#endif

    return res;
}

int main(){
    GetProcess();

    return 0;
}