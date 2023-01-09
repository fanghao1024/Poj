#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

const int max_n=1010;
const int max_e=20010;
struct Edge{
	int x,y,cost;
}edge[max_e];
bool cmp(const Edge& a,const Edge& b){
	return a.cost<b.cost;
}
int par[max_n];
int ranks[max_n];
void init(int n){
	for(int i=0;i<n;i++){
		par[i]=i;
		ranks[i]=0;
	}
}
int find(int x){
	if(par[x]==x){
		return x;
	}
	par[x]=find(par[x]);
	return par[x];
}
void unite(int x,int y){
	x=find(x);
	y=find(y);
	if(x!=y){
		if(ranks[x]>ranks[y]){
			par[y]=x;
		}else{
			par[x]=y;
			if(ranks[x]==ranks[y]){
				ranks[y]++;
			}
		}
	}
}
bool same(int x,int y){
	return find(x)==find(y);
}

int main(){
	int N,M;
	scanf("%d %d",&N,&M);
	for(int i=0;i<M;i++){
		scanf("%d %d %d",&edge[i].x,&edge[i].y,&edge[i].cost);
		edge[i].cost=-edge[i].cost;
	}
	sort(edge,edge+M,cmp);
	int ans=0;
	init(N+1);
	for(int i=0;i<M;i++){
		//printf("%d %d %d\n",edge[i].x,edge[i].y,edge[i].cost);
		if(!same(edge[i].x,edge[i].y)){
			
			unite(edge[i].x,edge[i].y);
			ans+=-edge[i].cost;
		}
	}
	bool flag=true;
	for(int i=1;i<N;i++){
		if(!same(i,i+1)){
			flag=false;
			break;
		}
	}
	if(flag){
		printf("%d\n",ans);
	}else{
		printf("-1\n");
	}
	
	return 0;
}
