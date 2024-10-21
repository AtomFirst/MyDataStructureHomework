#include<iostream>
#include<vector>
#include<algorithm>
#include<array>
#include<queue>

using namespace std;
using ll=long long;
using int2=array<int,2>;

#define all(x) x.begin(),x.end()

const int inf=1e9;

const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

void solve(){
    int n,m; cin>>n>>m;
    vector<string>maze(n);
    for(auto &l:maze)
        cin>>l;
    int2 s,e; cin>>s[0]>>s[1]>>e[0]>>e[1];
    if(maze[s[0]][s[1]]=='#'){
        cout<<0; return;
    }

    vector<vector<int>>dis(n,vector<int>(m,inf));
    dis[s[0]][s[1]]=0;
    queue<int2>q; q.emplace(s);
    while(q.size()){
        int x=q.front()[0],y=q.front()[1]; q.pop();
        //cerr<<"in "<<x<<" "<<y<<endl;
        int d=dis[x][y];
        for(int k=0;k<4;k++){
            int nx=x+dx[k],ny=y+dy[k];
            if(nx<0 or nx>=n or ny<0 or ny>=m or maze[nx][ny]=='#' or dis[nx][ny]<d+1)
                continue;
            dis[nx][ny]=d+1;
            q.emplace(int2{nx,ny});
        }
    }
    int res=dis[e[0]][e[1]];
    if(res==inf) res=0;
    cout<<res;
}

int main(){
    ios::sync_with_stdio(0),
        cin.tie(0),cout.tie(0);

    int t=1;
    //cin>>t;
    while(t--)
        solve();

    return 0;
}