#include<iostream>
#include<vector>
using namespace std;

// sort [begin,end)
template<typename T>
void HeapSort(T begin,T end){
    int n=end-begin;

	auto heapify=[&](auto&& self,int i)->void{
	    auto& cur=*(begin+i);
		int pl=i*2+1,pr=i*2+2;
		if(pr<n){
		    auto &l=*(begin+pl),&r=*(begin+pr);
			if(max(l,r)<=cur) return;
			if(l>r){
			    swap(l,cur);
				self(self,pl);
			}
			else{
			    swap(r,cur);
				self(self,pr);
			}
		}
		else if(pl<n && *(begin+pl)>cur)
		    swap(*(begin+pl),cur);
	};

    for(int i=n/2-1;i>=0;i--) heapify(heapify,i);

    while(--n){
        swap(*begin,*(begin+n));
		heapify(heapify,0);
    }
}

int main(){
    int n; cin>>n;
    vector<int>a(n);
    for(auto &x:a) cin>>x;

    HeapSort(a.begin(),a.end());
    cout<<"HeapSort: ";
    for(auto x:a) cout<<x<<" ";
    cout<<endl;

    return 0;
}