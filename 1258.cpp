#include<stdio.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int max_n=105;
int dis[max_n][max_n];
int par[max_n];
int ranks[max_n];
void init(int n){
	for(int i=0;i<n;i++){
		par[i]=i;
		ranks[i]=1;
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
struct Edge{
	int x,y;
	int dis;
	Edge(int x,int y,int dis){
		this->x=x;
		this->y=y;
		this->dis=dis;
	}
	bool operator<(const Edge& t) const{
		return this->dis>t.dis;
	}
};
int main(){
	int N;
	while(scanf("%d",&N)!=EOF){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				scanf("%d",&dis[i][j]);
			}
		}
		priority_queue<Edge> pq;
		for(int i=0;i<N;i++){
			for(int j=i+1;j<N;j++){
				pq.push(Edge(i,j,dis[i][j]));
			}
		}
		int ans=0;
		init(N);
		while(!pq.empty()){
			Edge e=pq.top();
			pq.pop();
			//printf("%d-%d\n",find(e.x),find(e.y));
			if(!same(e.x,e.y)){
				unite(e.x,e.y);
				ans+=e.dis;
			}
		}
		printf("%d\n",ans);
		
	}
	return 0;
}
