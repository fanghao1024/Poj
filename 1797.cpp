#include <iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;

const int max_n=1005;
const int max_e=1000005;
int N,M;
struct Edge{
	int s,e;
	int w;
}edge[max_e];
bool cmp(const Edge& a,const Edge& b){
	return a.w>b.w;
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
int main() {
	int Scen;
	scanf("%d",&Scen);
	for(int case_num=1;case_num<=Scen;case_num++){
		scanf("%d %d",&N,&M);
		build(N);
		for(int i=0;i<M;i++){
			scanf("%d %d %d",&edge[i].s,&edge[i].e,&edge[i].w);
		}
		sort(edge,edge+M,cmp);
		int ans;
		for(int i=0;i<M;i++){
			unite(edge[i].s,edge[i].e);
			if(same(1,N)){
				ans=i;
				break;
			}
		}
		printf("Scenario #%d:\n",case_num);
		printf("%d\n\n",edge[ans].w);
	}
	
	
	return 0;
}