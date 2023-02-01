#include <iostream>
#include<stdio.h>
#include<string.h>
#include<cmath>
#include<algorithm>
using namespace std;

int N,M;
int I,J,K;
int cnt;
int k;
const int max_n=40010;
int head[max_n];
struct Edge{
	int to,val,nxt;
}edge[max_n<<1];

void add_edge(int u,int v,int w){
	edge[++cnt].to=v;
	edge[cnt].val=w;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}

int F[max_n][20];
int dep[max_n];
int dis[max_n];

void dfs(int u){
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==F[u][0]){
			continue;
		}
		dep[v]=dep[u]+1;
		F[v][0]=u;
		dis[v]=dis[u]+edge[i].val;
		dfs(v);
	}
}
void ST_build(){
	for(int i=1;i<=k;i++){
		for(int j=1;j<=N;j++){
			F[j][i]=F[F[j][i-1]][i-1];
		}
	}
}

int LCA_query(int x,int y){
	if(dep[x]>dep[y]){
		swap(x,y);
	}
	for(int i=k;i>=0;i--){
		if(dep[F[y][i]]>=dep[x]){
			y=F[y][i];
		}
	}
	if(x==y){
		return x;
	}
	for(int i=k;i>=0;i--){
		if(dep[F[x][i]]!=dep[F[y][i]]){
			x=F[x][i];
			y=F[y][i];
		}
	}
	return F[x][0];
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&N,&M);
		cnt=0;
		k=int(log(N)/log(2.0));
		memset(head,0,sizeof(head));
		memset(dep,0,sizeof(dep));
		memset(dis,0,sizeof(dis));
		
		for(int i=1;i<N;i++){
			scanf("%d %d %d",&I,&J,&K);
			add_edge(I,J,K);
			add_edge(J,I,K);
		}

		dis[1]=0;
		dep[1]=1;
		F[1][0]=-1;
		dfs(1);
		ST_build();
		int x,y;
		while(M--){
			scanf("%d %d",&x,&y);
			int v=LCA_query(x, y);
			printf("%d\n",dis[x]+dis[y]-2*dis[v]);
		}
	}
	return 0;
}