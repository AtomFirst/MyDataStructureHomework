#include<iostream>
#include<vector>

using ll=long long;
using namespace std;

bool used[20][5];

int main(){
    int n; cin>>n;

    for(int i=1;i<=n;i++){
        int p; cin>>p;
        bool ok=0;
        for(int j=0;not ok and j<20;j++){
            int lx=0;
            for(int k=0;not ok and k<5;k++)
                if(not used[j][k]){
                    if(++lx>=p){
                        ok=1;
                        for(int l=0;l<p;l++)
                            used[j][k-p+1+l]=1,
                            cout<<(1+j*5+k-p+1+l)<<" ";
                    }
                }else
                    lx=0;
        }
        if(not ok){
            for(int j=0;p>0 and j<20;j++)
                for(int k=0;p>0 and k<5;k++)
                    if(not used[j][k])
                        used[j][k]=1,
                        cout<<(1+j*5+k)<<" ",
                        --p;
        }
        cout<<endl;
    }

    return 0;
}