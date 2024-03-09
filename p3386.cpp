#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1024;
int match[max_n];
bool vis[max_n];
int head[max_n],cnt;
struct Edge{
	int to,nxt;
}edge[max_n];
void init(){
	memset(head,-1,sizeof(head));
	
	memset(match,-1,sizeof(match));
	cnt=0;
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
int K,N,M,ans;
bool maxmatch(int u){
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(vis[v]) continue;
		vis[v]=1;
		if(match[v]==-1||maxmatch(match[v])){
			match[v]=u;
			return true;
		}
	}
	return false;
}
int main(){
	while(scanf("%d",&K)&&K){
		scanf("%d %d",&N,&M);
		int x,y;
		init();
		while(K--){
			scanf("%d %d",&x,&y);
			add_edge(x,y+N);
		}
		ans=0;
		for(int i=1;i<=N;i++){
			memset(vis,0,sizeof(vis));
			if(maxmatch(i)) ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
