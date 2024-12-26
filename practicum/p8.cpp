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

private:
    struct Node{
        Node(): num(0) {}

        T key[siz-1]; size_t num;
        Node* child[siz];
    };

    void debug(){
        cerr<<"BTree:\n";
        //
    }

       
       
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
    test();

    return 0;
}