#include<iostream>
#include<fstream>

using namespace std;

template<typename T>
class AVL{
public:
    AVL(): root(nullptr) {}

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
        Node* cur=root;

        while(cur!=nullptr)
            if(e < cur->elem)
                cur=cur->left;
            else if(e == cur->elem)
                return true;
            else
                cur=cur->right;

        return false;
    }

private:
    struct Node{
        Node(const T& elem): elem(elem),left(nullptr),right(nullptr),height(1),balance(0) {}

        T elem; int height,balance;
        Node *left,*right;
    };

    void debug(){
        cerr<<"AVL:\n";
        LrR(root,0);
    }

    Node* _insert(Node* cur,const T& e){
        if(cur==nullptr)
            return new Node(e);

        if(e < cur->elem)
            cur->left=_insert(cur->left,e);
        else
            cur->right=_insert(cur->right,e);

        UpdateNode(cur);
        cur=AdjustTree(cur);

        return cur;
    }

    Node* _erase(Node* cur,const T& e){
        if(e == cur->elem){
            if(cur->right==nullptr){
                Node* lst=cur;
                cur=cur->left;
                delete lst;
                return cur;
            }

            if(cur->left==nullptr){
                Node* lst=cur;
                cur=cur->right;
                delete lst;
                return cur;
            }

            T prev=MaxElem(cur->left);
            cur->left=_erase(cur->left,prev);
            cur->elem=prev;
        }
        else if(e < cur->elem)
            cur->left=_erase(cur->left,e);
        else
            cur->right=_erase(cur->right,e);

        UpdateNode(cur);
        cur=AdjustTree(cur);

        return cur;
    }

    // for debug
    void LrR(Node* cur,int d){
        if(cur==nullptr)
            return;
        
        LrR(cur->right,d+1);

        for(int i=0;i<d;i++)
            cerr<<" ";
        cerr<<(cur->elem)<<":"<<(cur->balance)<<endl;
        
        LrR(cur->left,d+1);
    }

    Node* AdjustTree(Node* cur){
        // keep balance
        if(cur->balance > 1){
            if(cur->left->balance < 0)
                cur->left=LeftRotate(cur->left);
            
            cur=RightRotate(cur);
        }
        else if(cur->balance < -1){
            if(cur->right->balance > 0)
                cur->right=RightRotate(cur->right);
            
            cur=LeftRotate(cur);
        }

        return cur;
    }

    Node* LeftRotate(Node* cur){
        Node* lst=cur;
        cur=cur->right;
        lst->right=cur->left;
        cur->left=lst;

        UpdateNode(lst);
        UpdateNode(cur);

        return cur;
    }

    Node* RightRotate(Node* cur){
        Node* lst=cur;
        cur=cur->left;
        lst->left=cur->right;
        cur->right=lst;
        
        UpdateNode(lst);
        UpdateNode(cur);

        return cur;
    }

    T MaxElem(Node* cur){
        while(cur->right) cur=cur->right;
        return cur->elem;
    }

    void UpdateNode(Node* cur){
        int lh=GetHeight(cur->left),rh=GetHeight(cur->right);
        cur->height=1+max(lh,rh);
        cur->balance=lh-rh;
    }

    int GetHeight(Node* cur){
        return cur?cur->height:0;
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
    
    AVL<int>st;

    for(int i=1;i<=10000;i++)
        if(is_prime(i))
            st.insert(i);

    fout.open("tree1.txt",ios::out);
    for(int i=200;i<=300;i++)
        fout<<i<<" "<<(st.contains(i)?"yes":"no")<<endl;
    fout.close();

    for(int i=500;i<=2000;i++)
        if(is_prime(i))
            st.erase(i);
    
    fout.open("tree2.txt",ios::out);
    for(int i=600;i<=700;i++)
        if(is_prime(i))
            fout<<i<<" "<<(st.contains(i)?"yes":"no")<<endl;
    fout.close();

    for(int i=2;i<=1000;i+=2)
        st.insert(i);

    fout.open("tree3.txt",ios::out);
    for(int i=100;i<=200;i+=2)
        fout<<i<<" "<<(st.contains(i)?"yes":"no")<<endl;
    fout.close();

    cout<<"Test done.\n";
}

int main(){
    test();

    return 0;
}