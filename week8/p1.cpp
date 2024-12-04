#include<iostream>
using namespace std;

template<typename T>
class BST{
public:
    BST():root(nullptr){}

    bool contain(const T& data){
        return find(data) != nullptr;
    }

    bool insert(const T& data){
        if(contain(data)) return false;
        if(root == nullptr)
            root = new Node{data,nullptr,nullptr};
        else{
            Node* cur = root;
            while(true)
                if(cur->data < data)
                    if(cur->right) cur = cur->right;
                    else break;
                else
                    if(cur->left) cur = cur->left;
                    else break;
            
            if(cur->data < data)
                cur->right = new Node{data,nullptr,nullptr};
            else
                cur->left = new Node{data,nullptr,nullptr};
        }
        return true;
    }

    bool erase(const T& data){
        Node* cur = find(data);
        if(cur == nullptr)
            return false;
        if(cur == root){
            if(cur->left == nullptr)
                root = cur->right;
            else if(cur->right == nullptr)
                root = cur->left;
            else{
                Node* min = cur->right;
                while(min->left != nullptr)
                    min = min->left;
                cur->data = min->data;
                cur = min;
            }
            delete cur;
        }
        else if(cur->left == nullptr){
            Node* tmp = cur;
            cur = cur->right;
            delete tmp;
        }
        else if(cur->right == nullptr){
            Node* tmp = cur;
            cur = cur->left;
            delete tmp;
        }
        else{
            Node* min = cur->right;
            while(min->left != nullptr)
                min = min->left;
            cur->data = min->data;
            delete min;
        }
        return true;
    }

private:
    struct Node{
        T data;
        Node* left;
        Node* right;
    };

    Node* find(const T& data){
        for(Node* cur = root;cur != nullptr;)
            if(cur->data == data)
                return cur;
            else if(cur->data < data)
                cur = cur->right;
            else
                cur = cur->left;
        return nullptr;
    }

    Node* root;
};

int main() {
    BST<int>bst;
    int m; cin>>m;
    while(m--){
        int op,x; cin>>op>>x;
        if(op == 1)
            cout<<"insert "<<x<<": "<<(bst.insert(x)?"done.":"already exists!")<<endl;
        else if(op == 2)
            cout<<"erase "<<x<<": "<<(bst.erase(x)?"done.":"not found!")<<endl;
        else if(op == 3)
            cout<<"find "<<x<<": "<<(bst.contain(x)?"found.":"not found!")<<endl;
    }
    return 0;
}