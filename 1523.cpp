#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1024;
int head[max_n],num[max_n],low[max_n],sccno[max_n],st[max_n],cnt,tot,dfn,top,son[max_n];
struct Edge{
	int to,nxt;
}edge[max_n<<1];
void init(){
	memset(head,-1,sizeof(head));
	cnt=tot=top=dfn=0;
	memset(num,0,sizeof(num));
	memset(low,0,sizeof(low));
	memset(sccno,0,sizeof(sccno));
	memset(son,0,sizeof(son));
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
int N,T,root;
void dfs(int u){
	num[u]=low[u]=++dfn;
	st[top++]=u;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(!num[v]){
			dfs(v);
			low[u]=min(low[u],low[v]);
			if(low[v]>=num[u]){
				//if(u==root) printf("~%d %d\n",u,v);
				son[u]++;
			}	
		}else if(!sccno[v]){
			low[u]=min(low[u],num[v]);
		}
	}
	if(num[u]==low[u]){
		tot++;
		while(1){
			int v=st[--top];
			sccno[v]=tot;
			if(v==u) break;
		}
	}
}
void tarjan(){
	root=1;
	dfs(root);
}
void solve(){
	if(T) printf("\n");
	printf("Network #%d\n",++T);
	int ans=0;
	for(int i=1;i<=N;i++){
		if(i==root){if(son[i]>1) ans++;}
		else if(son[i]>0) ans++;
	}
	//printf("~~%d %d\n",root,son[root]);
	if(!ans) printf("  No SPF nodes\n");
	else{
		for(int i=1;i<=N;i++){
			if(i==root){
				if(son[i]>1) printf("  SPF node %d leaves %d subnets\n",i,son[i]);
			}else if(son[i]) printf("  SPF node %d leaves %d subnets\n",i,son[i]+1);
		}
	}
}
int main(){
	int x,y;
	T=0;
	while(scanf("%d",&x)&&x){
		init();
		scanf("%d",&y);
		N=max(x,y);
		add_edge(x,y);
		add_edge(y,x);
		while(scanf("%d",&x)&&x){
			scanf("%d",&y);
			N=max(N,max(x,y));
			add_edge(x,y);
			add_edge(y,x);
		}
		
		tarjan();
		solve();
	}
	return 0;
}
