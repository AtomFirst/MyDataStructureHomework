#ifndef _ADTGRAPH
#define _ADTGRAPH 1

#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

typedef int status;
#define OK 1
#define ERROR 0
#define OVERFLOW -1

class Graph{
public:
    Graph(int maxn=200):maxn(maxn),val(new int[maxn+1]),vis(new bool[maxn+1]){
        adj = new int*[maxn+1];
        for(int i=0; i<=maxn; i++)
            adj[i] = new int[maxn+1];
    }
    Graph(initializer_list<pair<int,int>>edge){
        maxn = 0;
        for(auto [u,v]:edge)
            maxn = max(maxn, max(u,v));
        maxn;
        val = new int[maxn+1];
        vis = new bool[maxn+1];
        adj = new int*[maxn+1];
        for(int i=0; i<=maxn; i++)
            adj[i] = new int[maxn+1];
        for(auto [u,v]:edge)
            adj[u][v] = adj[v][u] = 1;
    }
    Graph(const Graph& g){
        maxn = g.maxn;
        val = new int[maxn+1];
        vis = new bool[maxn+1];
        adj = new int*[maxn+1];
        for(int i=0; i<=maxn; i++){
            adj[i] = new int[maxn+1];
            for(int j=0; j<=maxn; j++)
                adj[i][j] = g.adj[i][j];
        }
    }
    ~Graph(){
        delete[] val;
        for(int i=0; i<=maxn; i++)
            delete[] adj[i];
        delete[] adj;
    }
    int getVex(int i){
        return val[i];
    }
    int firstAdjVex(int i){
        for(int j=1; j<=maxn; j++)
            if(adj[i][j])
                return j;
        return -1;
    }
    int nextAdjVex(int i, int j){
        for(int k=j+1; k<=maxn; k++)
            if(adj[i][k])
                return k;
        return -1;
    }
    void dfsTraverse(int i,auto&& work){
        memset(vis,0,sizeof(bool)*maxn);
        dfs(i,work);
    }
    void bfsTraverse(int i,auto&& work){
        memset(vis,0,sizeof(bool)*maxn);
        queue<int>q;
        q.push(i);
        vis[i] = true;
        while(!q.empty()){
            int u = q.front(); q.pop();
            work(u);
            for(int j=firstAdjVex(u); j!=-1; j=nextAdjVex(u,j))
                if(!vis[j]){
                    q.push(j);
                    vis[j] = true;
                }
        }
    }
    void insertVex(int i,int v){
        val[i] = v;
    }
    void insertArc(int i,int j,bool undirected=false){
        adj[i][j] = 1;
        if(undirected)
            adj[j][i] = 1;
    }
    void deleteVex(int i){
        val[i] = 0;
        for(int j=1; j<=maxn; j++)
            adj[i][j] = 0;
        for(int j=1; j<=maxn; j++)
            adj[j][i] = 0;
    }
    void deleteArc(int i,int j,bool undirected=false){
        adj[i][j] = 0;
        if(undirected)
            adj[j][i] = 0;
    }
private:
    void dfs(int i,auto&& work){
        vis[i] = true; work(i);
        for(int j=firstAdjVex(i); j!=-1; j=nextAdjVex(i,j))
            if(!vis[j])
                dfs(j,work);
    }

    int maxn;
    int* val;
    int** adj;
    bool* vis;
};

#endif