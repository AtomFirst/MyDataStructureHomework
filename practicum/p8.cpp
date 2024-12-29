#include<iostream>
#include<fstream>

using namespace std;

template<typename T,size_t siz>
class BTree{
public:
    BTree(): root(nullptr) {}

    bool insert(const T& e){
        if(contains(e))
            return false;
        
        root=_insert(root,e);

        return true;
    }

    bool erase(const T& e){
        if(!contains(e))
            return false;

        root=_erase(root,e);

        return true;
    }

    bool contains(const T& e){
        

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

        T key[siz]; size_t num;
        Node* child[siz+1];
    };

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
            for(i=0;i<num;i++)
                if(e < cur->key[i])
                    break;

            bool of; T ne; Node* r;
            cur->child[i]=_insert(cur->chlid[i],e,of,ne,r);

            if(of){
                
            }
        }
        
    }

    void inorder(Node* cur,int d){
        if(cur==nullptr)
            return;
        
        for(int i=0;i<num;i++){
            inorder(cur->child[i],d+1);
            for(int i=0;i<d;i++)
                cerr<<" ";
            cerr<<cur->key[i]<<endl;
        }

        inorder(cur->child[num],d+1);
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
}

int main(){
    //test();

    return 0;
}