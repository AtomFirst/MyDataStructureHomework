#include "ADTGraph.cpp"

int main() {
    Graph g{{6,2},{6,4},{6,5},{1,4},{1,5},{2,3},{2,4},{4,5}};

    auto print = [](int i){cout << i << " ";};

    cout<<"DFS Traversal: ";
    g.dfsTraverse(1,print);
    cout << endl;

    cout<<"BFS Traversal: ";
    g.bfsTraverse(1,print);
    cout << endl;

    g.deleteVex(6);
    g.deleteArc(2,3,true);
    g.insertArc(2,5,true);
    g.insertArc(3,5,true);
    cout<<"delete 6,<2,3> \ninsert <2,5> <3,5>\n";

    cout<<"DFS Traversal: ";
    g.dfsTraverse(1,print);
    cout << endl;

    cout<<"BFS Traversal: ";
    g.bfsTraverse(1,print);
    cout << endl;

    return 0;
}