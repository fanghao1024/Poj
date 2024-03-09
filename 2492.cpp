#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=2010;
int par[max_n<<1];
void init(int n){
	for(int i=1;i<=n;i++) par[i]=i;
}
int find(int x){
	if(x!=par[x]) par[x]=find(par[x]);
	return par[x];
}
void unite(int x,int y){
	int rx=find(x),ry=find(y);
	if(rx!=ry){
		par[rx]=ry;
	}
}
bool same(int x,int y){return find(x)==find(y);}
int N,M;
int main(){
	int T,x,y;
	scanf("%d",&T);
	for(int caseNo=1;caseNo<=T;caseNo++){
		scanf("%d %d",&N,&M);
		init(2*N);
		bool flag=true;
		while(M--){
			scanf("%d %d",&x,&y);
			if(!flag) continue;
			unite(x,y+N);
			unite(x+N,y);
			if(same(x,x+N)||same(y,y+N)) flag=false;
		}
		if(caseNo-1) printf("\n");
		printf("Scenario #%d:\n",caseNo);
		if(flag) printf("No suspicious bugs found!\n");
		else printf("Suspicious bugs found!\n");
	}
	return 0;
}
