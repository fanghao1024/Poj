#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=210;
int N,M,K,cnt;
int head[max_n],vis[max_n],match[max_n];
struct Edge{
	int to,nxt;
}edge[max_n*max_n];

void init(){
	memset(head,-1,sizeof(head));
	memset(match,0,sizeof(match));
	cnt=0;
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
bool maxmatch(int u){
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(!vis[v]){
			vis[v]=1;
			if(!match[v]||maxmatch(match[v])){
				match[v]=u;
				return true;
			}
		}
	}
	return false;
}
int main(){
	int ids,x,y;
	while(scanf("%d",&N)&&N){
		scanf("%d %d",&M,&K);
		init();
		while(K--){
			scanf("%d %d %d",&ids,&x,&y);
			if(!x||!y) continue;
			add_edge(x,y+N-1);
		}
		int ans=0;
		for(int i=1;i<N;i++){
			memset(vis,0,sizeof(vis));
			if(maxmatch(i)) ans++;
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
