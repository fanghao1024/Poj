#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int max_n=1e4+10;
const int max_e=1e5+10;

int head[max_n],cnt,tot,low[max_n],num[max_n],dfn,sccno[max_n],N,M,st[max_n],top;
struct Edge{
	int to,nxt;
}edge[max_e];
void init(){
	memset(head,-1,sizeof(head));
	cnt=tot=dfn=top=0;
	memset(low,0,sizeof(low));
	memset(num,0,sizeof(num));
	memset(sccno,0,sizeof(sccno));
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void dfs(int u){
	st[top++]=u;
	low[u]=num[u]=++dfn;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(!num[v]){
			dfs(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!sccno[v]){
			low[u]=min(low[u],num[v]);
		}
	}
	if(num[u]==low[u]){
		tot++;
		while(1){
			int v=st[top--];
			sccno[v]=tot;
			if(num[v]==num[v]) break;
		}
	}
}
void tarjan(){
	for(int i=1;i<=N;i++){
		if(!sccno[i]) dfs(i);
	}
}
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		if(!N&&!M) break;
		init();
		int x,y;
		while(M--){
			scanf("%d %d",&x,&y);
			add_edge(x,y);
		}
		tarjan();
		if(tot==1) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
