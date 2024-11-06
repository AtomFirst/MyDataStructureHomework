#include<iostream>
#include<iomanip>
#include<vector>
#include<tuple>
using namespace std;

template<typename T>
struct Matrix{
    int n,m,maxRow,maxColumn;
    vector<tuple<int,int,T>>elem;

    Matrix(): n(0),m(0),maxRow(0),maxColumn(0) {}

    friend istream& operator>>(istream& in,Matrix &mtr){
        in>>mtr.n>>mtr.m;
        for(int i=0;i<mtr.n;i++)
            for(int j=0;j<mtr.m;j++){
                T tmp; in>>tmp;
                if(tmp==0) continue;
                mtr.maxRow=max(mtr.maxRow,i);
                mtr.maxColumn=max(mtr.maxColumn,j);
                mtr.elem.emplace_back(i,j,tmp);
            }
        return in;
    }

    friend ostream& operator<<(ostream& out,const Matrix &mtr){
        auto it=mtr.elem.begin();
        for(int i=0;i<mtr.n;i++,out<<endl)
            for(int j=0;j<mtr.m;j++){
                if(it!=mtr.elem.end()){
                    const auto &[r,c,e]=*it;
                    if(i==r and j==c){
                        out<<setw(2)<<e<<" ";
                        ++it;
                    }else
                        out<<setw(2)<<T(0)<<" ";
                }else
                    out<<setw(2)<<T(0)<<" ";
            }
        return out;
    }
};

template<typename T>
Matrix<T> NaiveTranspose(const Matrix<T> &mtr){
    Matrix<T> res;
    res.n=mtr.m; res.m=mtr.n;
    res.maxRow=mtr.maxColumn;
    res.maxColumn=mtr.maxRow;
    for(int i=0;i<=res.maxRow;i++)
        for(int j=0;j<=res.maxColumn;j++){
            for(const auto &[r,c,e]:mtr.elem)
                if(i==c and j==r){
                    res.elem.emplace_back(i,j,e);
                    break;
                }
        }
    return res;
}

template<typename T>
Matrix<T> QuickTranspose(const Matrix<T> &mtr){
    Matrix<T> res;
    res.n=mtr.m; res.m=mtr.n;
    res.maxRow=mtr.maxColumn;
    res.maxColumn=mtr.maxRow;
    res.elem.resize(mtr.elem.size());

    vector<int>cnt(1+res.maxRow);

    for(const auto &[r,c,e]:mtr.elem)
        ++cnt[c];
    
    vector<int>index(1+res.maxRow);
    for(int i=1;i<index.size();i++)
        index[i]=index[i-1]+cnt[i-1];

    for(const auto &[r,c,e]:mtr.elem){
        res.elem[index[c]++]={c,r,e};
    }   

    return res;
}

int main(){
    Matrix<int> matrix;
    cin>>matrix;
    cout<<"Before transpose:\n"<<matrix<<endl
        <<"Naive transpose:\n"<<NaiveTranspose(matrix)<<endl
        <<"Quick transpose:\n"<<QuickTranspose(matrix)<<endl;

    return 0;
}