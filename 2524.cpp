#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5e4+10;
int par[max_n];
int N,M;
void init(int n){
	for(int i=1;i<=n;i++) par[i]=i;
}
int find(int x){
	if(x!=par[x]){
		par[x]=find(par[x]);
	}
	return par[x];
}
void unite(int x,int y){
	int rx=find(x);
	int ry=find(y);
	if(rx!=ry){
		par[rx]=ry;
	}
}
int main(){
	int caseNo=1;
	while(scanf("%d %d",&N,&M)!=EOF){
		if(!N&&!M) break;
		init(N);
		int x,y;
		while(M--){
			scanf("%d %d",&x,&y);
			unite(x,y);
		}
		int ans=0;
		for(int i=1;i<=N;i++) if(i==par[i]) ans++;
		printf("Case %d: %d\n",caseNo++,ans);
	}
	return 0;
}
