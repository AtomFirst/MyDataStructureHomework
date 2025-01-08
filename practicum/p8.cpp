#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

template<typename T,size_t siz>
class BTree{
public:
    BTree(): root(nullptr) {}

    bool insert(const T& e){
        if(contains(e))
            return false;
        
        bool of; T ne; Node* r;
        root=_insert(root,e,of,ne,r);

        if(of){
            Node* cur=new Node;

            cur->num=1;
            cur->key[0]=ne;
            cur->child[0]=root;
            cur->child[1]=r;
            
            root=cur;
        }

        return true;
    }

    bool erase(const T& e){
        if(!contains(e))
            return false;

        _erase(root,e,nullptr,-1);

        return true;
    }

    bool contains(const T& e){
        for(Node* cur=root;cur!=nullptr;){
            int i;
            for(i=0;i< cur->num;i++)
                if(e < cur->key[i])
                    break;
                else if(e == cur->key[i])
                    return true;
            
            cur=cur->child[i];
        }

        return false;
    }

    void debug(){
        cerr<<"BTree:\n";

        inorder(root,0);
    }

private:
    struct Node{
        Node(): num(0){
            for(auto& p:child)
                p=nullptr;
        }

        T key[siz]; int num;
        Node* child[siz+1];
    };

#define SHIFT_LEFT(ARR,L,R) \
    for(int _=(L);_<=(R);++_) ARR[_-1]=ARR[_];

#define SHIFT_RIGHT(ARR,L,R) \
    for(int _=(R);_>=(L);--_) ARR[_+1]=ARR[_];

#define MOVE(DIST,SRC,L,R) \
    for(int _=(L);_<=(R);++_) (DIST)[_]=(SRC)[_];

    Node* _insert(Node* cur,const T& e,bool& overflow,T& up,Node*& right){
        overflow=false;

        if(cur==nullptr){ 
            cur=new Node;
            cur->num=1;
            cur->key[0]=e;

            return cur;
        }

        if(cur->child[0]!=nullptr){
            int i;
            for(i=0;i< cur->num;i++)
                if(e < cur->key[i])
                    break;

            bool of; T ne; Node* r;
            cur->child[i]=_insert(cur->child[i],e,of,ne,r);

            if(of){
                //for(int j=cur->num - 1;j>=i;j--)
                //    cur->key[j+1]=cur->key[j];
                SHIFT_RIGHT(cur->key,i,cur->num - 1)

                //for(int j=cur->num;j>i;j--)
                //    cur->child[j+1]=cur->child[j];
                SHIFT_RIGHT(cur->child,i+1,cur->num)

                cur->key[i]=ne;
                cur->child[i+1]=r;

                if(++(cur->num) > siz-1)
                    overflow=true;
            }
        }
        else{
            int i;

            for(i=0;i < cur->num;i++)
                if(e < cur->key[i])
                    break;
            
            //for(int j=cur->num - 1;j>=i;j--)
            //    cur->key[j+1]=cur->key[j];
            SHIFT_RIGHT(cur->key,i,cur->num - 1)

            cur->key[i]=e;

            if(++(cur->num) > siz-1)
                overflow=true;
        }
        
        if(overflow){
            int mid=siz/2;

            up=cur->key[mid];
            cur->num=mid;

            right=new Node;
            right->num=siz-mid-1;

            //for(int i=0;i < right->num;i++)
            //    right->key[i]=cur->key[mid+1+i];
            MOVE(right->key,cur->key +mid+1,0,right->num - 1)

            //for(int i=0;i <= right->num;i++)
            //    right->child[i]=cur->child[mid+1+i];
            MOVE(right->child,cur->child +mid+1,0,right->num)
        }

        return cur;
    }

    void _erase(Node*& cur,const T& e,Node* parent,int id){
        {
            int i;  bool eq=false;

            for(i=0;i< cur->num;i++)
                if(e < cur->key[i])
                    break;
                else if(e == cur->key[i]){
                    eq=true;
                    break;
                }
            
            if(!eq)
                _erase(cur->child[i],e,cur,i);
            else if(cur->child[0]!=nullptr){
                T nxt=MinElem(cur->child[i+1]);
                cur->key[i]=nxt;
                _erase(cur->child[i+1],nxt,cur,i+1);
            }
            else{
                //for(int j=i;j< cur->num;j++)
                //    cur->key[j]=cur->key[j+1];
                SHIFT_LEFT(cur->key,i+1,cur->num -1)
                
                --(cur->num);
            }
        }

        const int min_key=(siz+1)/2-1;

        if(cur->num >= min_key)
            return;

        // underflow

        // cur is root
        if(parent==nullptr){
            if(cur->num==0)
                cur=nullptr;
            return;
        }

        // cur is not root
        bool hasl=id-1 >= 0,
            hasr=id+1 <= parent->num;
        
        Node *lsib=hasl? parent->child[id-1]:nullptr,
            *rsib=hasr? parent->child[id+1]:nullptr;
        
        // borrow from left sibling
        if(hasl && lsib->num > min_key){
            //for(int i=cur->num - 1;i>=0;i--)
            //    cur->key[i+1]=cur->key[i];
            SHIFT_RIGHT(cur->key,0,cur->num - 1)

            //for(int i=cur->num;i>=0;i--)
            //    cur->child[i+1]=cur->child[i];
            SHIFT_RIGHT(cur->child,0,cur->num)

            cur->key[0]=parent->key[id-1];
            cur->child[0]=lsib->child[lsib->num];
            ++(cur->num);

            parent->key[id-1]=lsib->key[lsib->num - 1];
            --(lsib->num);

            return;
        }

        // borrow from right sibling
        if(hasr && rsib->num > min_key){
            cur->key[cur->num]=parent->key[id];
            cur->child[cur->num + 1]=rsib->child[0];
            ++(cur->num);

            parent->key[id]=rsib->key[0];

            //for(int i=0;i < rsib->num;i++)
            //    rsib->key[i]=rsib->key[i+1];
            SHIFT_LEFT(rsib->key,1,rsib->num - 1)

            //for(int i=0;i <= rsib->num;i++)
            //    rsib->child[i]=rsib->child[i+1];
            SHIFT_LEFT(rsib->child,1,rsib->num)

            --(rsib->num);

            return;
        }

        // merge with left sibling
        if(hasl){
            lsib->key[lsib->num]=parent->key[id-1];

            //for(int i=0;i < cur->num;i++)
            //    lsib->key[lsib->num +1+i]=cur->key[i];
            MOVE(lsib->key + lsib->num +1,cur->key,0,cur->num - 1)

            //for(int i=0;i <= cur->num;i++)
            //   lsib->child[lsib->num +1+i]=cur->child[i];
            MOVE(lsib->child + lsib->num +1,cur->child,0,cur->num)

            lsib->num += 1 + cur->num;

            delete cur;

            SHIFT_LEFT(parent->key,id,parent->num - 1)
            SHIFT_LEFT(parent->child,id+1,parent->num)

            --(parent->num);

            return;
        }

        // merge with right sibling
        if(hasr){
            cur->key[cur->num]=parent->key[id];

            MOVE(cur->key + cur->num +1,rsib->key,0,rsib->num - 1)
            MOVE(cur->child + cur->num +1,rsib->child,0,rsib->num)

            cur->num += 1 + rsib->num;

            delete rsib;

            SHIFT_LEFT(parent->key,id+1,parent->num - 1)
            SHIFT_LEFT(parent->child,id+2,parent->num)

            --(parent->num);

            return;
        }


        // error
        cerr<<"_erase() underflow and cannot fix!"<<endl;
    }

    T MinElem(Node* cur){
        while(cur->child[0]) 
            cur=cur->child[0];
        
        return cur->key[0];
    }

    void inorder(Node* cur,int d){
        if(cur==nullptr)
            return;
        
        const int w=6;

        for(int i=0;i < cur->num;i++){
            inorder(cur->child[i],d+1);
            
            for(int i=0;i<d*w;i++)
                cerr<<" ";
            
            if(cur->num > 1){
                if(i==0) 
                    cerr<<"^";
                else if(i==cur->num-1)
                    cerr<<"v";
                else
                    cerr<<"~";
            }else
                cerr<<"o";

            cerr<<setw(3)<<cur->key[i];
            cerr<<endl;
        }

        inorder(cur->child[cur->num],d+1);
    }

    Node* root;   
};

bool is_prime(int n){
    if(n<2) return 0;
    
    for(int i=2;i*i<=n;i++)
        if(n%i==0)
            return 0;
    
    return 1;
}

void test(){
    ofstream fout;
    
    BTree<int,4>st;

    for(int i=1;i<=10000;i++)
        if(is_prime(i))
            st.insert(i);

    fout.open("b-tree1.txt",ios::out);
    
    for(int i=200;i<=300;i++)
        fout<<i<<" "<<(st.contains(i)?"yes":"no")<<endl;
    
    fout.close();

    for(int i=500;i<=2000;i++)
        if(is_prime(i))
            st.erase(i);
    
    fout.open("b-tree2.txt",ios::out);
    
    for(int i=600;i<=700;i++)
        if(is_prime(i))
            fout<<i<<" "<<(st.contains(i)?"yes":"no")<<endl;
    
    fout.close();

    for(int i=2;i<=1000;i+=2)
        st.insert(i);

    fout.open("b-tree3.txt",ios::out);
    
    for(int i=100;i<=200;i+=2)
        fout<<i<<" "<<(st.contains(i)?"yes":"no")<<endl;
    
    fout.close();

    cout<<"Test done.\n";

    //st.debug();
}

const char hint[]="\
B-Tree\n\n\
MENU:\n\
+ x    insert x\n\
- x    erase x\n\
? x    query x\n\
p      print tree\n\
q      quit\n\n";

void Interactive(){
    cout<<hint;

    BTree<int,3>st;

    for(string str;cout<<"> ",cin>>str;)
        if(str=="+"){
            int x; cin>>x;
            if(!st.insert(x))
                cout<<"already existed!"<<endl;
        }else if(str=="-"){
            int x; cin>>x;
            if(!st.erase(x))
                cout<<"not found!"<<endl;
        }else if(str=="?"){
            int x; cin>>x;
            cout<<(st.contains(x)?"existed":"not existed")<<endl;
        }else if(str=="p"){
            st.debug(); cout<<endl;
        }else if(str=="q"){
            return;
        }else{
            cout<<"invaild input!"<<endl;
        }
}

int main(){

#ifdef INTERACT
    Interactive();
#else
    test();
#endif

    return 0;
}