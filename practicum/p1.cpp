#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<cstring>
#include<chrono>
#include<ctime>
#include<tuple>

#if defined(_WIN32)
#include<conio.h>  
#endif

using namespace std;

template<typename T>
struct SLinkNode{
    SLinkNode(): 
        next(nullptr) {}

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
    DLinkNode(): 
        next(nullptr),prev(nullptr) {}

    DLinkNode(const T& elem): 
        elem(elem),next(nullptr),prev(nullptr) {}
    
    ~DLinkNode(){
        delete next;
    }

    T elem;
    DLinkNode *next,*prev;
};

// erase element if work return true
template<typename T>
void traverse(SLinkNode<T>* head,int count,auto &&work){
    for(SLinkNode<T> *prev=head,*cur=prev->next;
        cur!=nullptr && count>0;--count)
            if(work(cur->elem)){
                prev->next=cur->next;
                cur->next=nullptr;
                delete cur;
                cur=prev->next;
            }else{
                prev=cur;
                cur=cur->next;
            }
}

// erase element if work return true
template<typename T>
void traverse(DLinkNode<T>* head,int count,auto &&work){
    for(DLinkNode<T> *prev=head,*cur=prev->next;
        cur!=nullptr && count>0;--count)
            if(work(cur->elem)){
                prev->next=cur->next;
                cur->next=nullptr;
                delete cur;
                cur=prev->next;
            }else{
                prev=cur;
                cur=cur->next;
            }
}

template<typename T>
int list_length(SLinkNode<T>* list){
    int len=0;
    
    auto counter=[&](auto &&x){
        ++len;
        return false;
    };

    traverse(list,1e9,counter);

    return len;
}

template<typename T>
int list_length(DLinkNode<T>* list){
    int len=0;
    
    auto counter=[&](auto &&x){
        ++len;
        return false;
    };

    traverse(list,1e9,counter);

    return len;
}

template<typename T>
void BubbleSort(SLinkNode<T>* head,auto cmp){
    int len=0;

    for(auto p=head->next;p!=nullptr;p=p->next)
        ++len;
    
    for(bool flag=false;len>1 && !flag;--len,flag=false){
        SLinkNode<T> *p0=head,*p1=p0->next,*p2=p1->next;

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

template<typename T>
void BubbleSort(DLinkNode<T>* head,auto cmp){
    int len=0;

    for(auto p=head->next;p!=nullptr;p=p->next)
        ++len;
    
    for(bool flag=false;len>1 && !flag;--len,flag=false){
        DLinkNode<T> *p0=head,*p1=p0->next,*p2=p1->next;

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
        return 
            out<<"PID: "<<p.pid
                <<", NAME: "<<p.name
                <<", MEM(K): "<<p.mem;
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

    char buf[0x400];

#if defined(__linux__)
    fin.getline(buf,0x3ff,'\n');
    for(process p;
        fin>>buf
            >>p.pid
            >>buf>>buf>>buf
            >>p.mem
            >>buf>>buf>>buf>>buf
            >>p.name;
        fin.getline(buf,0x3ff,'\n')){
            auto cur=new SLinkNode<process>(p);
            cur->next=res; res=cur;
        }
#elif defined(_WIN32)
    for(process p;fin.getline(buf,0x3ff,'\n');){
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

using process_start=tuple<process,chrono::time_point<chrono::system_clock>>;
using process_end_dur=tuple<process,chrono::time_point<chrono::system_clock>,chrono::duration<double>>;

const int max_rows=10;

void react(){
    auto t1=chrono::system_clock().now();

    auto alive=new SLinkNode<process_start>;

    auto deadhead=new DLinkNode<process_end_dur>,
        deadtail=deadhead;

    int cnt=0;

    while(true){
        // exit when input 'q'
#if defined(_WIN32)
        while(kbhit()){
            char c=getch();
            if(c=='q'){
                cout<<"exit"<<endl;
                return;
            }
        }
#endif

        // react each seconds
        auto t2=chrono::system_clock().now();
        if(t2-t1<1s) continue; t1=t2;

        SLinkNode<process>* cur=GetProcess();
        BubbleSort(cur,[](const process& a,const process& b){
            return a.mem>b.mem;
        });

        // print alive process list
#if defined(__linux__)
    const char cmd[]="clear";
#elif defined(_WIN32)
    const char cmd[]="cls";
#endif
        system(cmd);
        
        cout<<"count: "<<(++cnt)<<endl;

        cout<<"Alive Process (head "<<max_rows
            <<", all: "<<list_length(cur)<<"):"
            <<endl;
        
        traverse(cur,max_rows,[](const process& p){
            cout<<p<<endl;
            return false;
        });

        auto cur_contains_p=[&](const process& p){
            bool has_p=false;

            auto contains_p=[&](const process& _p){
                if(_p.pid==p.pid)
                    has_p=true;
                
                return false;
            };

            traverse(cur,1e9,contains_p);
        
            return has_p;
        };

        // update dead process list
        // erase which appear
        
        traverse(deadhead,1e9,[&](const process_end_dur& ped){
            const auto &[p,e,d]=ped;
            return cur_contains_p(p);
        });
        // append which disappear (also erase them from alive process list)
        traverse(alive,1e9,[&](const process_start& ps){
            const auto &[p,s]=ps;
            bool has_p=cur_contains_p(p);

            if(has_p) return false;

            auto node=new DLinkNode<process_end_dur>;
            node->next=nullptr;
            deadtail->next=node;
            node->prev=deadtail;
            deadtail=node;

            auto &[_p,e,d]=node->elem;
            _p=p; e=t2; d=e-s;

            return true;
        });

        // update alive process list
        // append which appear
        traverse(cur,1e9,[&](const process& p){
            bool has_p=false;

            auto contains_p=[&](const process_start& ps){
                const auto &[_p,s]=ps;
                if(_p.pid==p.pid)
                    has_p=true;
                
                return false;
            };

            traverse(alive,1e9,contains_p);

            if(!has_p){
                auto node=new SLinkNode<process_start>;
                node->next=alive->next;
                alive->next=node;

                auto &[_p,s]=node->elem;
                _p=p; s=t2;
            }

            return false;
        });
        

        delete cur;

        BubbleSort(deadhead,[](const process_end_dur& a,const process_end_dur& b){
            const auto &[ap,ae,ad]=a;
            const auto &[bp,be,bd]=b;
            return ad<bd;
        });

        // print dead process list
        cout<<endl<<"Dead Process (head "<<max_rows
            <<", all: "<<list_length(deadhead)<<"):"
            <<endl;
        
        traverse(deadhead,max_rows,[](const process_end_dur& ped){
            const auto &[p,e,d]=ped;

            auto _e=chrono::system_clock::to_time_t(e);
            char* buffer=ctime(&_e);
            buffer[19]='\0';

            cout<<p<<" end_time("<<(buffer+11)<<") duration:"<<d.count()<<"s"<<endl;

            return false;
        });
    }
}

int main(){
    react();

    return 0;
}