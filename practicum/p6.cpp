#include<iostream>
#include<vector>
#include<algorithm>
#include<array>
#include<numeric>

using namespace std;

using int3=array<int,3>;

#define all(x) x.begin(),x.end()

class DSU{
public:
    DSU(int n):fa(n+1){
        iota(all(fa),0);
    }
    
    int getf(int x){
        return x==fa[x]?x:fa[x]=getf(fa[x]);
    }
    
    bool conn(int x,int y){
        return getf(x)==getf(y);
    }

    void merge(int x,int y){
        fa[getf(x)]=getf(y);
    }
    
private:
    vector<int>fa;
};

int main(){
    int n,m; cin>>n>>m;
    vector<int3>edge(m);
    
    for(auto &[u,v,w]:edge)
        cin>>u>>v>>w;

    sort(edge.begin(),edge.end(),[](const int3 &a,const int3 &b){
        return a[2]<b[2];
    });

    DSU dsu(n);

    for(auto [u,v,w]:edge){
        if(!dsu.conn(u,v))
            dsu.merge(u,v);
        
        if(dsu.conn(1,n)){
            cout<<w<<endl;
            return 0;
        }
    }

    cout<<-1<<endl;

    return 0;
}