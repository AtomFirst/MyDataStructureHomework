#include "ADTQueue.cpp"
#include<iomanip>

int main(){
    int m; cin>>m;
    Queue<int>q;
    for(int i=1;i<=m;i++){
        cout<<"["<<setw(2)<<i<<"]: ";
        string opt; int x; cin>>opt;
        if(opt=="enqueue") cin>>x;
        bool ok; int t=-1;
        if(opt=="clear"){
            q.clear();
            cout<<"CLEAR Q\n";
        }else if(opt=="empty"){
            cout<<"Q "<<(q.empty()?"is":"is't")<<" EMPTY\n";
        }else if(opt=="length"){
            cout<<"LENGTH OF Q: "<<q.length()<<"\n";
        }else if(opt=="getHead"){
            ok=q.getHead(t);
            if(ok)
                cout<<"Head OF Q: "<<t<<"\n";
            else
                cout<<"Q is empty, can't getHead!\n";
        }else if(opt=="traverse"){
            cout<<"Q: ";
            q.traverse();
        }else if(opt=="enqueue"){
            q.push(x);
            cout<<"ENQUEUE "<<x<<"\n";
        }else if(opt=="dequeue"){
            ok=q.pop(t);
            if(ok)
                cout<<"DEQUEUE "<<t<<"\n";
            else
                cout<<"Q is empty, can't pop!\n";
        }else{
            cerr<<"INVAILD INPUT!\n";
            exit(-1);
        }   
    }

    return 0;
}