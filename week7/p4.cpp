#include<cstdio>
#include<algorithm>
using namespace std;

int n,m,ans=0,cs=0;
int f[5001];

struct bian{
	int x,y,z;
}b[200001];

bool cmp(bian a,bian b){
	return a.z<b.z;
}

void csh(){
	for(int i=0;i<5001;i++)
	f[i]=i;
}

int getf(int x){
	if(f[x]==x)return x;
	return f[x]=getf(f[x]);
}

int main(){
	csh();
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	scanf("%d%d%d",&b[i].x,&b[i].y,&b[i].z);
	sort(b,b+m,cmp);

	for(int i=0;i<m;i++){
		if(cs==n-1)break;
		if(getf(b[i].x)==getf(b[i].y))continue;
		f[getf(b[i].x)]=getf(b[i].y);
		cs++;
		ans=ans+b[i].z;
    }

	if(cs<n-1)printf("Could not complete the task!\n");
	else printf("%d\n",ans);

	return 0;
}