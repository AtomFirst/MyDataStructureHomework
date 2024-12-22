#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include<stack>

using namespace std;

const int maxn=110;

int n,m;
char maze[maxn][maxn];

bool loading_data(const char filename[]){
    ifstream fin(filename,ios::in);
    
    if(!fin.is_open()){
        cerr<<"Cannot open "<<filename<<"!\n";
        return false;
    }
    
    fin>>n>>m;
    
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            fin>>maze[i][j];

    fin.close();

    return true;
}

bool in_map(int x,int y){
    return 1<=x && x<=n && 1<=y && y<=m;
};

const int dx[]{0,0,-1,1},dy[]{-1,1,0,0};

int path[maxn][maxn];
bool visited[maxn][maxn];

bool find_way(int sx,int sy,int ex,int ey){
    memset(visited,0,sizeof(visited));
    memset(path,-1,sizeof(path));

    stack<tuple<int,int,int,int>>s;
    s.emplace(sx,sy,0,0);

    while(s.size()){
        auto &[x,y,d,i]=s.top();

        if(i==4){
            path[x][y]=-1; s.pop(); 
            continue;
        }
        
        if(i==0) path[x][y]=d,visited[x][y]=1;

        if(x==ex && y==ey) break;

        int nx=x+dx[i],ny=y+dy[i];
        ++i;

        if(!in_map(nx,ny) || visited[nx][ny] || maze[nx][ny]=='#') continue;

        s.emplace(nx,ny,d+1,0);
    }

    return !s.empty();
}

void show(){
    const int w=2;

    cout<<endl;

    for(int i=1;i<=n;i++){
        cout<<setw(w)<<setfill('0')<<i<<" ";

        for(int j=1;j<=m;j++){
            if(path[i][j]<0)
                cout<<setw(w)<<setfill(' ')<<maze[i][j]<<" ";
            else
                cout<<setw(w)<<setfill(' ')<<path[i][j]<<" ";
        }
        
        cout<<endl;
    }

    cout<<setw(w)<<setfill(' ')<<"X/Y";

    for(int i=1;i<=m;i++)
        cout<<setw(w)<<setfill('0')<<i<<" ";
    
    cout<<endl<<endl;
}

int main(){
    memset(path,-1,sizeof(path));

    cout<<"Loading data... ";
    
    if(!loading_data("input/maze.txt"))
        return 0;
    
    cout<<"done.\n\nMAP:\n";

    show();

    cout<<"\nInput start_x start_y end_x end_y(input '0 0 0 0' to exit):\n";

    for(int sx,sy,ex,ey;cin>>sx>>sy>>ex>>ey;){
        if(!sx && !sy && !ex && !ey) break;

        if(!in_map(sx,sy)){
            cout<<"Start point out of bound!\n";
            continue;
        }

        if(!in_map(ex,ey)){
            cout<<"End point out of bound!\n";
            continue;
        }

        if(maze[sx][sy]=='#'){
            cout<<"Start point is wall!\n";
            continue;
        }

        if(maze[ex][ey]=='#'){
            cout<<"End point is wall!\n";
            continue;
        }

        if(find_way(sx,sy,ex,ey))
            show();
        else
            cout<<"Could not reach end point from start point!\n";
    }

    return 0;
}