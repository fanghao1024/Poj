#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=2e5+10;
int par[max_n],d[max_n];
int N,M;
void init(){
	for(int i=0;i<=N;i++){
		par[i]=i;
		d[i]=0;
	}
}
int find(int x){
	if(x!=par[x]){
		int f=par[x];
		par[x]=find(par[x]);
		d[x]+=d[f];
	}
	return par[x]; 
}
void unite(int x,int y,int v){
	int rx=find(x);
	int ry=find(y);
	if(rx!=ry){
		par[rx]=ry;
		d[rx]=d[y]+v-d[x];
	}
}
int main(){
	scanf("%d %d",&N,&M);
	init();
	int a,b,v;
	int ans=0;
	while(M--){
		scanf("%d %d %d",&a,&b,&v);
		a--;
		int ra=find(a);
		int rb=find(b);
		if(ra==rb){
			if(d[a]-d[b]!=v) ans++;
		}else{
			unite(a,b,v);
		}
	}
	printf("%d\n",ans);
	return 0;
}
