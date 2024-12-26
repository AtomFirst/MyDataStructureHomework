#include<iostream>
#include<fstream>
#include<chrono>
#include<algorithm>

using namespace std;

const int N=10,SIZE=100'000;

int n,siz[N];
int* input[N];

void loading_data(){
    ifstream fin("input/data9.txt",ios::in);

    fin>>n;
    
    for(int i=0;i<n;i++){
        fin>>siz[i];

        if(input[i]==nullptr)
            input[i]=new int[siz[i]];

        for(int j=0;j<siz[i];j++)
            fin>>input[i][j];    
    }

    fin.close();
}

/*
#include<cstdlib>
void check(const char name[]){
    ofstream fout((string(name)+".txt").c_str(),ios::out);

    for(int i=0;i<N;i++){
        for(int j=0;j<siz[i];j++)
            fout<<input[i][j]<<' ';
        fout<<endl;
    }

    fout.close();

    system(("diff ans.txt "+string(name)+".txt").c_str());
}
*/

void test(void (*sort)(int* arr,int n),const char name[]){
    loading_data();
    cout<<name<<": "; cout.flush();
    
    for(int i=0;i<N;i++){
        auto start=chrono::steady_clock::now();
        sort(input[i],siz[i]);
        auto end=chrono::steady_clock::now();

        chrono::duration<double> seconds=end-start;
        cout<<seconds.count()<<"s ";
        cout.flush();
    }

    cout<<endl;

    //check(name);
}

template<typename T>
void StraightInsertionSort(T* arr,int n){
    for(int i=1;i<n;i++){
        int j; T tmp=arr[i];

        for(j=i-1;j>=0;j--)
            if(arr[j]>tmp)
                arr[j+1]=arr[j];
            else
                break;
        
        arr[j+1]=tmp;
    }
}

template<typename T>
void ShellSort(T* arr,int n){
    // Hibbard
    int k=1; while((1<<k)-1<n) ++k; --k;

    for(int step=(1<<k)-1;step;step>>=1)
        for(int i=step;i<n;i++){
            int j; T tmp=arr[i];

            for(j=i-step;j>=0;j-=step)
                if(arr[j]>tmp)
                    arr[j+step]=arr[j];
                else
                    break;
            
            arr[j+step]=tmp;
        }
}

template<typename T>
void BubbleSort(T* arr,int n){
    for(int r=n;r>1;r--){
        bool done=true;

        for(int i=0;i+1<r;i++)
            if(arr[i]>arr[i+1])
                swap(arr[i],arr[i+1]),
                done=false;
        
        if(done) break;
    }
}

template<typename T>
void _QuickSort(T* arr,int l,int r){
    if(r-l<2) return;
    
    T key=arr[l]; int pl=l,pr=r-1;
    while(pl<pr){
        while(pl<pr && arr[pr]>=key) --pr;
        arr[pl]=arr[pr];

        while(pl<pr && arr[pl]<key) ++pl;
        arr[pr]=arr[pl];
    }
    arr[pl]=key;

    _QuickSort(arr,l,pl);
    _QuickSort(arr,pl+1,r);
}

template<typename T>
void QuickSort(T* arr,int n){
    _QuickSort(arr,0,n);
}

template<typename T>
void SelectSort(T* arr,int n){
    for(int i=0;i+1<n;i++){
        T mn=arr[i]; int p=i;

        for(int j=i+1;j<n;j++)
            if(mn>arr[j])
                mn=arr[j],p=j;
        
        swap(arr[i],arr[p]);
    }
}

template<typename T>
void HeapSort(T* arr,int n){
    auto AdjustHeap=[&](int x){
        while(x*2+1<n){
            T &a=arr[x],&b=arr[x*2+1];
            if(x*2+2<n){
                T &c=arr[x*2+2];
                if(b>c){
                    if(b>a)
                        swap(a,b),
                        x=x*2+1;
                    else
                        break;
                }else
                    if(c>a)
                        swap(a,c),
                        x=x*2+2;
                    else
                        break;
            }else{
                if(a<b) 
                    swap(a,b),
                    x=x*2+1;
                else 
                    break;
            }
        }
    };

    for(int i=n-1;i>=0;i--)
        AdjustHeap(i);

    while(n>1){
        swap(arr[0],arr[--n]);
        AdjustHeap(0);
    }
}

int buffer[SIZE];

void _MergeSort(int* arr,int l,int r){
    if(r-l<2) return;
    
    int m=l+(r-l)/2;

    _MergeSort(arr,l,m);
    _MergeSort(arr,m,r);

    int i=l,p1=l,p2=m;
    while(p1<m && p2<r){
        if(arr[p1]<arr[p2])
            buffer[i++]=arr[p1++];
        else
            buffer[i++]=arr[p2++];
    }

    while(p1<m)
        buffer[i++]=arr[p1++];

    while(p2<r)
        buffer[i++]=arr[p2++];

    for(int i=l;i<r;i++)
        arr[i]=buffer[i];
}

void MergeSort(int* arr,int n){
    _MergeSort(arr,0,n);
}

void RadixSort(int* arr,int n){
    int mx=arr[0];
    for(int i=1;i<n;i++)
        if(mx<arr[i]) 
            mx=arr[i];
    int num=0; for(;mx;mx/=10) ++num;

    int start[11];
    
    for(int l=0,k=1;l<num;l++,k*=10){
        for(auto &x:start) x=0;

        auto GetDigit=[&](int x){
            return x/k%10;
        };

        for(int i=0;i<n;i++)
            ++start[GetDigit(arr[i])+1];
        
        for(int i=1;i<10;i++)
            start[i]+=start[i-1];

        for(int i=0;i<n;i++)
            buffer[start[GetDigit(arr[i])]++]=arr[i];

        for(int i=0;i<n;i++)
            arr[i]=buffer[i];
    }
}

int cnt[10'000];
pair<int,int> num_freq[10'000];

void testCountingSort(){
    loading_data();
    cout<<"计数排序: "; cout.flush();

    auto start=chrono::steady_clock::now();
    
    for(int i=0;i<siz[2];i++)
        ++cnt[input[2][i]];

    auto end=chrono::steady_clock::now();

    chrono::duration<double> seconds=end-start;
    cout<<seconds.count()<<"s (sample3)"<<endl;

    cout<<"(number,frequency): ";

    for(int i=0;i<10'000;i++)
        num_freq[i]={i,cnt[i]};
    
    sort(num_freq,num_freq+10'000,[](pair<int,int> a,pair<int,int> b){
        return a.second>b.second;
    });

    for(int i=0;i<10'000;i++){
        if(num_freq[i].second<=0) break;
        cout<<"("<<num_freq[i].first<<","<<num_freq[i].second<<") ";
    }

    cout<<endl;
}

int main(){
    test(StraightInsertionSort,"直接插入排序");
    test(ShellSort,"希尔排序");
    test(BubbleSort,"冒泡排序");
    test(QuickSort,"快速排序");
    test(SelectSort,"选择排序");
    test(HeapSort,"堆排序");
    test(MergeSort,"归并排序");
    test(RadixSort,"基数排序");
    
    testCountingSort();

    return 0;
}