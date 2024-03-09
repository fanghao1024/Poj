#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e5+10;

int N,K,cnt,maxLen;
int head[max_n],dis[max_n],pre[max_n];
struct Edge{
	int to,w;
	int nxt;
}edge[max_n<<1];
void add(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=1;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
}
void dfs1(int u,int fa,int d){
	dis[u]=d;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa) continue;
		dfs1(v,u,d+edge[i].w);
		pre[v]=i;
	}
}
void dfs2(int u,int fa){
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to,w=edge[i].w;
		if(v==fa) continue;
		dfs2(v,u);
		maxLen=max(maxLen,dis[u]+dis[v]+w);
		dis[u]=max(dis[u],dis[v]+w);
	}
}
int main(){
	scanf("%d %d",&N,&K);
	int x,y;
	init();
	for(int i=1;i<N;i++){
		scanf("%d %d",&x,&y);
		add(x,y,1);
		add(y,x,1);
	}
	dfs1(1,0,0);
	int s=1;
	for(int i=1;i<=N;i++) if(dis[i]>dis[s]) s=i;
	memset(pre,-1,sizeof(pre));
	dfs1(s,0,0);
	int t=1;
	for(int i=1;i<=N;i++) if(dis[i]>dis[t]) t=i;
	int L1=dis[t];
	if(K==1){
		printf("%d\n",(N-1)*2-(L1-1));
		return 0;
	}
	for(int i=pre[t];;i=pre[edge[i^1].to]){
		int first=edge[i^1].to,second=edge[i].to;
		edge[i].w=-edge[i].w;
		edge[i^1].w=-edge[i^1].w;
		if(first==s) break;
	}
	maxLen=0;
	memset(dis,0,sizeof(dis));
	dfs2(1,0);
	printf("%d\n",(N-1)*2-(L1-1)-(maxLen-1));
	return 0;
}
