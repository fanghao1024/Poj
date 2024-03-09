#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=2e4+10;
const int max_m=5e4+10;

int head[max_n],cnt,N,M,ans[max_m<<1],tot;
struct Edge{
	int to,nxt;
	bool flag;
}edge[max_m<<1];
void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	edge[cnt].flag=0;
	head[x]=cnt++;
}
void dfs(int u){
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		if(!edge[i].flag){
			edge[i].flag=1;
			dfs(edge[i].to);
		}
	}
	ans[tot++]=u;
}
int main(){
	scanf("%d %d",&N,&M);
	init();
	int x,y;
	while(M--){
		scanf("%d %d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	tot=0;
	dfs(1);
	for(int i=0;i<tot;i++) printf("%d\n",ans[i]);
	return 0;
}
