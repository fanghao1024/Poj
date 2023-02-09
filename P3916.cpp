#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int N,M;
const int max_n=100010;
struct Node{
	int to,nxt;
}edge[max_n];
int head[max_n];
int cnt;
void add(int u,int v){
	edge[cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt++;
}
/*
int par[max_n];
void init(){
	for(int i=1;i<=N;i++)
		par[i]=i;
}
int find(int x){
	if(par[x]!=x){
		par[x]=find(par[x]);
	}
	return par[x];
}

void unite(int x,int y){
	int a=find(x);
	int b=find(y);
	if(a!=b){
		if(a>b){
			par[b]=a;
		}else{
			par[a]=b;
		}
	}
}
*/
bool vis[max_n];
int ans[max_n];
void dfs(int u,int v){
	if(ans[v]==-1){
		ans[v]=u;
	}
	vis[v]=1;
	for(int i=head[v];i!=-1;i=edge[i].nxt){
		if(vis[edge[i].to]==0){
			ans[edge[i].to]=u;
			dfs(u,edge[i].to);
		}
	}
}
int main() {
	scanf("%d %d",&N,&M);
	int u,v;
	cnt=0;
	memset(head,-1,sizeof(head));
	memset(vis,0,sizeof(vis));
	memset(ans,-1,sizeof(ans));
	for(int i=0;i<M;i++){
		scanf("%d %d",&u,&v);
		add(v,u);
	}
	for(int i=N;i;i--){
		dfs(i,i);
	}
	for(int i=1;i<=N;i++){
		if(i!=1) printf(" ");
		printf("%d",ans[i]);
	}
	printf("\n");
	return 0;
}