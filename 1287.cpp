#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int max_n=55;
const int max_e=10005;
int N,M;
struct Edge{
	int s,e;
	int cost;
}edge[max_e];
bool cmp(const Edge& a,const Edge& b){
	return a.cost<b.cost;
}
int par[max_n];
int ranks[max_n];
void build(int n){
	for(int i=1;i<=n;i++){
		par[i]=i;
		ranks[i]=1;
	}
}
int find(int x){
	if(x!=par[x]){
		par[x]=find(par[x]);
	}
	return par[x];
}
void unite(int x,int y){
	int a=find(x);
	int b=find(y);
	if(a!=b){
		if(ranks[a]>ranks[b]){
			par[b]=a;
		}else{
			par[a]=b;
			if(ranks[a]==ranks[b]){
				ranks[b]++;
			}
		}
	}
}
bool same(int x,int y){
	return find(x)==find(y);
}
int main(){
	while(scanf("%d",&N)&&N){
		scanf("%d",&M);
		int x,y,z;
		for(int i=0;i<M;i++){
			scanf("%d %d %d",&x,&y,&z);
			edge[i].s=x;
			edge[i].e=y;
			edge[i].cost=z;
		}
		sort(edge,edge+M,cmp);
		build(N);
		int ans=0;
		int count=1;
		for(int i=0;i<M;i++){
			int s=edge[i].s;
			int e=edge[i].e;
			int c=edge[i].cost;
			if(!same(s,e)){
				ans+=c;
				unite(s,e);
				count++;
			}
			if(count==N) break;
		}
		printf("%d\n",ans);
	}
	return 0;
}
