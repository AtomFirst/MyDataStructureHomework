#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<array>

using namespace std;

using int2=array<int,2>;

class BusMap{
public:
    bool load_data(const char filename[]){
        ifstream fin(filename,ios::in);

        if(!fin.is_open()){
            cerr<<"Cannot open "<<filename<<"!\n";
            return false;
        }

        //线路名 站点 公交线路ID 线内ID 站点ID
        string route,station;
        int rid,rsid,sid,lstrid=-1,lstsid;
        for(;fin>>route>>station>>rid>>rsid>>sid;lstrid=rid,lstsid=sid){
            station_n2i[station]=sid;
            station_i2n[sid]=station;

            route_n2i[route]=rid;
            route_i2n[rid]=route;

            g2[{sid,rid}].emplace(int2{sid,-1},1);
            g2[{sid,-1}].emplace(int2{sid,rid},1);

            if(rid!=lstrid) continue;
            
            g[sid].emplace(lstsid);
            g[lstsid].emplace(sid);

            uvw[{sid,lstsid}]=rid;
            uvw[{lstsid,sid}]=rid;

            g2[{sid,rid}].emplace(int2{lstsid,rid},0);
            g2[{lstsid,rid}].emplace(int2{sid,rid},0);
        }

        fin.close();

        return true;
    }

    void debug(){
        cerr<<"station count: "<<station_i2n.rbegin()->first<<endl;
    }

    void ans1(){
        string start,end; cin>>start>>end;

        if(station_n2i.count(start)==0){
            cout<<"Cannot find "<<start<<"!\n";
            return;
        }

        if(station_n2i.count(end)==0){
            cout<<"Cannot find "<<end<<"!\n";
            return;
        }
        
        if(start==end){
            cout<<"Already arrived!\n";
            return;
        }

        // dijkstra
        int2 s{station_n2i[start],-1},e{station_n2i[end],-1};
        map<int2,int2>prev; map<int2,int>dist; map<int2,bool>vis;
        priority_queue<pair<int,int2>>q; bool ok=0;
        q.emplace(0,s); dist[s]=0;

        while(q.size() && !ok){
            auto [dis,cur]=q.top(); q.pop();
            dis=-dis; if(vis[cur]) continue;
            vis[cur]=true;

            for(auto [nxt,wgt]:g2[cur]){
                int new_dis=dis+wgt;

                if(dist.count(nxt) && dist[nxt]<=new_dis)
                    continue;
                
                dist[nxt]=new_dis;
                prev[nxt]=cur;
                q.emplace(-new_dis,nxt);

                if(nxt==e){
                    ok=1; break;
                }
            }
        }

        if(!ok){
            cout<<"Cannot reach "<<end<<" from "<<start<<"!\n";
            return;
        }

        vector<int2>path{e};
        while(path.back()!=s)
            path.emplace_back(prev[path.back()]);
        reverse(path.begin(),path.end());

        int n=path.size(),res=dist[e]/2-1;
        cout<<"Mininum transfer numbers path :\n(all "<<res<<" transfers)\n";

        int lst_transfer;
        for(int i=0;i<n;i++)
            if(path[i][1]==-1){
                cout<<station_i2n[path[i][0]];

                if(i!=n-1)
                    cout<<"\n |\n | ";

                lst_transfer=i;
            }
            else if(path[i+1][1]==-1)
                cout<<route_i2n[path[i][1]]
                    <<" "<<(i-lst_transfer-1)<<" stations"
                    <<"\n |\n";

        cout<<endl<<endl;
    }

    void ans2(){
        string start,end; cin>>start>>end;

        if(station_n2i.count(start)==0){
            cout<<"Cannot find "<<start<<"!\n";
            return;
        }

        if(station_n2i.count(end)==0){
            cout<<"Cannot find "<<end<<"!\n";
            return;
        }
        
        if(start==end){
            cout<<"Already arrived!\n";
            return;
        }

        // bfs
        int s=station_n2i[start],e=station_n2i[end];
        map<int,int>prev; queue<int>q; bool ok=0; 
        q.emplace(s); 

        while(q.size() && !ok){
            int cur=q.front(); q.pop();

            for(int nxt:g[cur]){
                if(prev.count(nxt)) continue;
                prev[nxt]=cur;
                q.emplace(nxt);

                if(nxt==e){
                    ok=1; break;
                }
            }
        }

        if(!ok){
            cout<<"Cannot reach "<<end<<" from "<<start<<"!\n";
            return;
        }

        vector<int>path{e};
        while(path.back()!=s)
            path.emplace_back(prev[path.back()]);
        reverse(path.begin(),path.end());
        
        int n=path.size();
        cout<<"Mininum station numbers path :\n(all "<<(n-1)<<" stations)\n\n";

        for(int i=0;i<n;i++){
            cout<<station_i2n[path[i]];

            if(i!=n-1)
                cout<<"\n |\n | "
                    <<route_i2n[uvw[{path[i],path[i+1]}]]
                    <<"\n |\n";
        }

        cout<<endl<<endl;
    }

private:
    map<int,set<int>>g;
    map<int2,set<pair<int2,int>>>g2;
    map<int2,int>uvw; // uvw[{u,v}] is a edge from u to v

    map<string,int>station_n2i; // name to id
    map<int,string>station_i2n;

    map<string,int>route_n2i; // name to id
    map<int,string>route_i2n;
};

const char hint[]="\
Bus Map\n\n\
MENU:\n\
1 start_station end_station    output a path from start to end which the number of transfer is mininum\n\
2 start_station end_station    output a path which go past mininum station\n\
0    exit this program\n\n";

int main(){
    BusMap busmap;
    
    cout<<"Loading data... ";

    if(!busmap.load_data("input/南京市公交线路.txt"))
        return 0;
    
    cout<<"done.\n\n"<<hint;

    //busmap.debug(); return 0;

    for(int opt;cout<<"> ",cin>>opt;){
        if(opt==0) 
            break;
        else if(opt==1)
            busmap.ans1();
        else if(opt==2)
            busmap.ans2();
        else 
            cout<<"Invaild input!\n";
    }

    return 0;
}