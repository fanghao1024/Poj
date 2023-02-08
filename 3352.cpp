#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int max_n=1002;
const int max_e=2010;
int cnt;
int head[max_n];
bool vis[max_n];
int fdn[max_n];
int low[max_n];
int degree[max_n];
struct Edge{
	int to;
	int nxt;
}edge[max_e];
int N,R,nums;
int ans;
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void tarjan(int u,int fa){
	fdn[u]=low[u]=++nums;
	vis[u]=1;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa) continue;
		if(!vis[v]){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}else{
			low[u]=min(low[u],fdn[v]);
		}
	}
}
int main(){
	scanf("%d %d",&N,&R);
	memset(head,-1,sizeof(head));
	memset(vis,0,sizeof(vis));
	cnt=0;
	int x,y;
	for(int i=0;i<R;i++){
		scanf("%d %d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	nums=0;
	ans=0;
	tarjan(1,1);
	memset(degree,0,sizeof(degree));
	for(int i=1;i<=N;i++){
		for(int j=head[i];j!=-1;j=edge[j].nxt){
			if(low[i]!=low[edge[j].to]){
				degree[low[i]]++;
			}
		}
	}
	for(int i=1;i<=N;i++){
		if(degree[i]==1) ans++;
	}
	printf("%d\n",(ans+1)/2);
	return 0;
}

