#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=100005;
int trie[max_n*32][2];
int head[max_n];
int dis[max_n];
struct Edge{
	int to,w;
	int nxt;
}edge[max_n<<1];
int cnt,N,ans,tc;
void add_edge(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=w;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void dfs(int u,int p){
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		int w=edge[i].w;
		if(v==p) continue;
		dis[v]=dis[u]^w;
		dfs(v,u);
	}
}
void insert(int num){
	int p=0;
	for(int i=30;i>=0;i--){
		bool c=num&(1<<i);
		if(!trie[p][c]){
			trie[p][c]=tc++;
		}
		p=trie[p][c];
	}
}
int find(int num){
	int p=0;
	int res=0;
	for(int i=30;i>=0;i--){
		bool c=num&(1<<i);
		if(trie[p][c^1]){
			p=trie[p][c^1];
			res+=1<<i;
		}else{
			p=trie[p][c];
		}
	}
	return res;
}
int main(){
	
	while(scanf("%d",&N)!=EOF){
		int x,y,w;
		memset(head,-1,sizeof(head));
		memset(trie,0,sizeof(trie));
		cnt=0;
		for(int i=1;i<N;i++){
			scanf("%d %d %d",&x,&y,&w);
			x++;
			y++;
			add_edge(x,y,w);
			add_edge(y,x,w);
		}
		dis[1]=0;
		dfs(1,-1);
		ans=0;
		tc=1;
		insert(dis[1]);
		for(int i=2;i<=N;i++){
			ans=max(ans,find(dis[i]));
			insert(dis[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
