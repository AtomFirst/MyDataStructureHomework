#include<iostream>
#include<iomanip>
#include<vector>
#include<tuple>
#include<algorithm>
using namespace std;

#define all(x) x.begin(),x.end()

template<typename T>
struct Matrix{
    int n,m;
    vector<vector<T>> elem;

    Matrix(): n(0),m(0) {}

    friend istream& operator>>(istream& in,Matrix &mtr){
        in>>mtr.n>>mtr.m;
        mtr.elem.resize(mtr.n,vector<T>(mtr.m));
        for(auto &line:mtr.elem)
            for(auto &e:line)
                in>>e;
        return in;
    }

    friend ostream& operator<<(ostream& out,const Matrix &mtr){
        for(const auto &line:mtr.elem){
            for(const auto &e:line)
                out<<setw(2)<<e<<" ";
            out<<endl;
        }
        return out;
    }
};

template<typename T>
vector<tuple<int,int,T>> GetSaddlePoint(const Matrix<T> &mtr){
    vector<int> mn(mtr.n),mx(mtr.m);
    for(int i=0;i<mtr.n;i++)
        mn[i]=*min_element(all(mtr.elem[i]));
    for(int j=0;j<mtr.m;j++)
        for(int i=0;i<mtr.n;i++)
            mx[j]=max(mx[j],mtr.elem[i][j]);
    
    vector<tuple<int,int,T>> res;
    for(int i=0;i<mtr.n;i++)
        for(int j=0;j<mtr.m;j++)
            if(mtr.elem[i][j]==mn[i] and mtr.elem[i][j]==mx[j])
                res.emplace_back(i,j,mtr.elem[i][j]);
    return res;
}

int main(){
    Matrix<int> matrix;
    cin>>matrix;
    auto res=GetSaddlePoint(matrix);
    for(const auto &[r,c,e]:res)
        cout<<"("<<r<<","<<c<<","<<e<<")"<<endl;

    return 0;
}