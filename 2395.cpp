#include<stdio.h>
#include<algorithm>
using namespace std;

const int max_n=2005;
const int max_e=10010;
struct Edge{
	int x,y,cost;
	bool operator<(const Edge& temp)const{
		return this->cost<temp.cost;
	}
};
Edge edge[max_e];
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
	}
	sort(edge,edge+M);
	init(N+1);
	int ans=-1;
	int count=0;
	for(int i=0;i<M;i++){
		if(!same(edge[i].x,edge[i].y)){
			unite(edge[i].x,edge[i].y);
			ans=edge[i].cost;
			count++;
			if(count==N-1){
				break;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
