#include "ADTGraph.cpp"

int main() {
    int n,m; cin>>n>>m;
    
    Graph g(n);

    for(int i=0;i<m;i++) {
        int u,v; cin>>u>>v;
        g.insertArc(u,v,true);
    }

    auto print = [](int i){cout << i << " ";};

    cout<<"DFS Traversal: ";
    g.dfsTraverse(1,print);
    cout << endl;

    cout<<"BFS Traversal: ";
    g.bfsTraverse(1,print);
    cout << endl;

    return 0;
}