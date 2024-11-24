#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<map>
using namespace std;

vector<string> HuffmanCoding(const vector<int>& freq){
    map<int,int>left,right,index;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
    int tot=freq.size();
    for(int i=0;i<tot;i++)
        index[i]=i,
        q.emplace(freq[i],i);
    while(q.size()>1){
        auto [fx,ix]=q.top(); q.pop();
        auto [fy,iy]=q.top(); q.pop();
        ++tot;
        left[tot]=ix; right[tot]=iy;
        q.emplace(fx+fy,tot);
    }
    int root=tot;
    vector<string>res(freq.size());
    string path;
    auto dfs=[&](auto&& self,int x){
        if(index.count(x)){
            res[index[x]]=path;
            return;
        }
        if(left.count(x)) 
            path+="0",
            self(self,left[x]),
            path.pop_back();
        if(right.count(x))
            path+="1",
            self(self,right[x]),
            path.pop_back();
    };
    dfs(dfs,root);
    return res;
}

int main(){
    int n; cin>>n;
    vector<int>f(n);
    for(int &x:f) cin>>x;
    auto&& res=HuffmanCoding(f);
    for(int i=0;i<n;i++) 
        cout<<i<<": "<<res[i]<<endl;
    return 0;
}