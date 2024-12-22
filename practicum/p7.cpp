#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<set>
#include<queue>

using namespace std;

class BusMap{
public:
    void load_data(const char filename[]){
        ifstream fin(filename,ios::in);

        //线路名 站点 公交线路ID 线内ID 站点ID
        string line,station;
        int lid,lsid,sid,lstlid=-1,lstsid;
        for(;fin>>line>>station>>lid>>lsid>>sid;lstlid=lid,lstsid=sid){
            station_n2i[station]=sid;
            station_i2n[sid]=station;

            if(lid==lstlid)
                g[sid].emplace(lstsid),
                g[lstsid].emplace(sid);
        }

        fin.close();
    }

    void ans1(){

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
        map<int,int>pre; queue<int>q; bool ok=0; 
        pre[s]=-1; q.emplace(s); 

        while(q.size() && !ok){
            int cur=q.front(); q.pop();

            for(int nxt:g[cur]){
                if(pre.count(nxt)) continue;
                pre[nxt]=cur;
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
            path.emplace_back(pre[path.back()]);
        reverse(path.begin(),path.end());
        
        int n=path.size();
        cout<<"Mininum station numbers path: \n";

        for(int i=0;i<n;i++)
            cout<<station_i2n[path[i]]<<(i<n-1?" -> ":"\n");
    }

private:
    map<int,set<int>>g;
    map<string,int>station_n2i; // name to id
    map<int,string>station_i2n;
};

const char hint[]="\
MENU:\n\
1 start_station end_station    output a path from start to end which the number of transfer is mininum\n\
2 start_station end_station    output a path which go past mininum station\n\
0    exit this program\n\n";

int main(){
    BusMap busmap;
    
    cout<<"Loading data... ";
    busmap.load_data("input/南京市公交线路.txt");
    cout<<"done.\n\n"<<hint;

    for(int opt;cin>>opt;){
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