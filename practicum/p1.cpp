#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<chrono>

using namespace std;

template<typename T>
struct SLinkNode{
    SLinkNode(): next(nullptr) {}

    SLinkNode(const T& elem): 
        elem(elem),next(nullptr) {}
    
    ~SLinkNode(){
        delete next;
    }

    T elem;
    SLinkNode* next;
};

template<typename T>
struct DLinkNode{
    DLinkNode(): next(nullptr),prev(nullptr) {}

    DLinkNode(const T& elem): 
        elem(elem),next(nullptr),prev(nullptr) {}
    
    ~DLinkNode(){
        delete next;
    }

    T elem;
    DLinkNode *next,*prev;
};

template<typename T>
void traverse(SLinkNode<T>* head,auto &&work){
    for(head=head->next;head!=nullptr;head=head->next)
        work(head->elem);
}

template<typename T>
void BubbleSort(T* head,auto cmp){
    int len=0;

    for(auto p=head->next;p!=nullptr;p=p->next)
        ++len;
    
    for(bool flag=false;len>1 && !flag;--len,flag=false){
        T *p0=head,*p1=p0->next,*p2=p1->next;

        for(int i=0;i+1<len;i++,p0=p1,p1=p2,p2=p2->next)
            if(!cmp(p1->elem,p2->elem)){
                p0->next=p2;
                p1->next=p2->next;
                p2->next=p1;
                swap(p1,p2);

                flag=true;
            }
    }
}

struct process{
    friend ostream& operator<<(ostream& out,const process& p){
        return out<<"PID: "<<p.pid<<", NAME: "<<p.name<<", MEM(K):"<<p.mem;
    }

    int pid;
    string name;
    int mem;
};

// return a SLinkList with head node.
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
    for(process p;fin.getline(buf,0xff,'\n');){
        // get data from csv
        for(int i=0,j=0,n=strlen(buf);i<n;++i,++j){
            while(i<n && buf[i]!='\"') ++i;
            int l=++i;
            while(i<n && buf[i]!='\"') ++i;
            int r=i;

            if(j==0)
                p.name=string(buf+l,buf+r);
            else if(j==1)
                p.pid=stoi(string(buf+l,buf+r));
            else if(j==4){
                p.mem=0;
                for(int k=l;k<r;k++)
                    if(isdigit(buf[k]))
                        p.mem=p.mem*10+(buf[k]-'0');
            }
        }

        auto cur=new SLinkNode<process>(p);
        cur->next=res; res=cur;
    }
#endif

    auto head=new SLinkNode<process>;
    head->next=res; res=head;

    return res;
}

void react(){
    auto t1=chrono::system_clock().now();

    auto alive=new SLinkNode<tuple<process,chrono::time_point<chrono::system_clock>>>;

    auto deadhead=new DLinkNode<tuple<process,chrono::time_point<chrono::system_clock>,chrono::duration<double>>>;

    while(true){
        // exit when input 'q'
        // TODO

        // react each seconds
        auto t2=chrono::system_clock().now();
        if(t2-t1<1s) continue; t1=t2;

        SLinkNode<process>* cur=GetProcess();
        BubbleSort(cur,[](const process& a,const process& b){
            return a.mem>b.mem;
        });

        // TODO

        auto print1=[](auto x){
            auto [p,t]=x;
            // TODO
        };

        traverse(alive,print1);
        // TODO
    }
}

int main(){
    react();

    return 0;
}