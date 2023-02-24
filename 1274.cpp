#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=210;
int N,M,cnt;
int head[max_n];
bool vis[max_n<<1];
int match[max_n<<1];
struct Edge{
	int to,nxt;
}edge[max_n*max_n];
void add(int u,int v){
	edge[cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt++;
}
void init(){
	memset(head,-1,sizeof(head));
	memset(match,0,sizeof(match));
	cnt=0;
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
	while(scanf("%d %d",&N,&M)!=EOF){
		init();
		int s,k;
		for(int i=1;i<=N;i++){
			scanf("%d",&s);
			while(s--){
				scanf("%d",&k);
				add(i,k+N);
			}
		}
		int ans=0;
		for(int i=1;i<=N;i++){
			memset(vis,0,sizeof(vis));
			if(maxmatch(i)) ans++;
		}
		printf("%d\n",ans);
	}	
	return 0;
}
