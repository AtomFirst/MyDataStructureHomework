#include<iostream>
#include<map>
using namespace std;

class BiTree{
public:
    BiTree(): root(0) {}
    friend istream& operator>>(istream& in, BiTree& tree){
        tree.root=1;
        int n; in>>n;
        for(int i=1;i<=n;i++)
            in>>tree.left[i]>>tree.right[i];
        return in;
    }
    int weight(){
        if(root==0) return 0;

        map<int,int>d2c;
        auto dfs=[&](auto&& self,int x,int d){
            if(x==0) return;
            ++d2c[d];
            self(self,left[x],d+1);
            self(self,right[x],d+1);    
        };
        dfs(dfs,root,0);

        int res=0;
        for(auto [d,c]:d2c)
            res=max(res,c);
        return res;
    }

private:

    int root;
    map<int,int>left,right;
};

int main(){
    BiTree tree;
    cin>>tree;
    cout<<tree.weight()<<endl;

    return 0;
}