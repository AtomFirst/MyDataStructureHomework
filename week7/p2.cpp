#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int main(){
    int n,m; cin>>n>>m;

    vector<vector<pair<int,int>>>g(n+1);
    for(int i=1,u,v,w;i<=m;i++)
        cin>>u>>v>>w,
        g[u].push_back({v,w}),
        g[v].push_back({u,w});

    const int inf=1e9;
    vector<int>dis(n+1,inf);

    auto dijkstra=[&](int s){
        vector<int>vis(n+1);
        priority_queue<pair<int,int>>q;
        q.push({0,s}); dis[s]=0;
        while(!q.empty()){
            auto [d,u]=q.top(); d=-d; q.pop();
            if(vis[u]) continue; vis[u]=1;
            for(auto [v,w]:g[u])
                if(dis[v]>d+w)
                    dis[v]=d+w,
                    q.push({-dis[v],v});
        }
    };

    dijkstra(1);

    for(int i=1;i<=n;i++)
        cout<<i<<":"<<dis[i]<<" ";
    cout<<endl;

    return 0;
}