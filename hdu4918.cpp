#include <iostream>
#include <cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=101000;
const int inf=max_n+10;
int N,Q,cnt,root,S,pl,tot,ans;
int rec[max_n],head[max_n],f[max_n],s[max_n],ids[max_n],Fa[max_n],cur[max_n];
int dis[20][max_n];
bool vis[max_n];
int Pool[max_n*40];
struct Edge{
	int to,nxt;
}edge[max_n<<1]; 
struct BIT{//树状数组 
	int *C,n;
	void init(int T){//初始化 
		n=T;
		C=Pool+pl;
		pl+=n+1;
		for(int i=0;i<=n;i++)
			C[i]=0;
	}
	int que(int x){//查询前缀和 
		x++;
		int res=0;
		for(int i=x;i;i-=(i&-i))
			res+=C[i];
		return res;
	}
	void update(int x,int y){//点更新 
		x++;
		for(int i=x;i<=n;i+=(i&-i))
			C[i]+=y;
	} 
}bit[max_n][2];//两个树状数组
/*
struct Bit{
	int *C,n;
	void init(int T){
		n=T;
		C=Pool+pl;
		pl+=n+1;
		for(int i=0;i<=n;i++){
			C[i]=0;
		}
	}
	void update(int x,int d){
		x++;
		for(int i=x;i<=n;i+=(i&-i)){
			C[i]+=d;
		}
	}
	int que(int x){
		int res=0;
		x++;
		for(int i=x;i>0;i-=(i&-i)){
			res+=C[i];
		}
		return res;
	}
}bit[max_n][2];


void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}*/
void add_edge(int u,int v){
	edge[cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt++;
}
void getroot(int u,int fa){//求解重心
	s[u]=1;
	f[u]=0;//删除u后，最大子树的大小 
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=fa&&!vis[v]){
			getroot(v,u);
			s[u]+=s[v];
			f[u]=max(f[u],s[v]);
		}
	}    
	f[u]=max(f[u],S-s[u]);//S为当前子树总结点数 
	if(f[u]<f[root])
		root=u;
}
/*
void get_root(int u,int fa){
	s[u]=1;
	f[u]=0;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=fa&&!vis[v]){
			get_root(v, u);
			s[u]+=s[v];
			f[u]=max(f[u],s[v]);
		}
	}
	f[u]=max(f[u],S-s[u]);
	if(f[u]<f[root]) root=u;
}*/
/*
void dfs(int cur_dep,int id_num,int u,int d,int fa){
	dis[cur_dep][u]=d;
	bit[id_num][0].update(dis[cur_dep][u], rec[u]);
	if(cur_dep>1) bit[id_num][1].update(dis[cur_dep-1][u],rec[u]);
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(!vis[v]&&v!=fa){
			dfs(cur_dep,id_num,v,d+1,u);
		}
	}
}*/
void dfs(int dep,int idx,int u,int d,int fa){
	dis[dep][u]=d;
	bit[idx][0].update(dis[dep][u],rec[u]);  //将u节点的权值w[u]插入到第1个树状树状的dis[][]+1位置，dis[dep-1][u]表示u到当前层重心的距离 
	if(dep>1)                           //当前层次大于1，说明存在上一级重心 
	bit[idx][1].update(dis[dep-1][u],rec[u]);//将w[u]插入到第2个树状树状的dis[][]+1位置，dis[dep-1][u]表示u到上一层重心的距离 
	for(int i=head[u];i!=-1;i=edge[i].nxt){//u的每一个邻接点v 
		int v=edge[i].to;
		if(v!=fa&&!vis[v])
			dfs(dep,idx,v,d+1,u); //从v出发，深度优先遍历，距离+1 
	}
}

void solve(int u,int fa){//u为当前重心，fa为上一级重心 
	vis[u]=1;
	ids[u]=++tot;
	Fa[ids[u]]=ids[fa];//F[]表示上一级重心编号，id[u]表示u节点的编号
	cur[ids[u]]=cur[ids[fa]]+1;//cur[]表示当前节点所属重心的层次，等于上一级重心的层次+1 
	bit[tot][0].init(S+1);//初始化第1个树状数组，0空间不用，因此节点数S+1 
	bit[tot][1].init(S+1);//初始化第2个树状数组
	dfs(cur[ids[u]],ids[u],u,0,0);//从u开始深度优先遍历

	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(vis[v]||v==fa) continue;
		root=0;
		//S=size[u]>size[v]?size[v]:tmp-size[u];//?什么时候出现<=的情况？在原树中当前的root是邻接点v的子节点
		//getroot(v,u); //求以v为根的子树的重心
		S=s[v];
		getroot(v,0);
		solve(root,u); //递归求解 
	}
}
/*
void solve(int u,int fa){
	vis[u]=true;
	ids[u]=++tot;
	Fa[ids[u]]=ids[fa];
	cur[ids[u]]=cur[ids[fa]]+1;
	bit[ids[u]][0].init(S+1);
	bit[ids[u]][1].init(S+1);
	dfs(cur[ids[u]],ids[u],u,0,0);
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=fa&&!vis[v]){
			root=0;
			S=s[v];
			get_root(v,0);
			solve(root,u);
		}
	}
}
*/
void update(int idx,int x,int d){
	bit[idx][0].update(dis[cur[idx]][x],d);
	if(Fa[idx]){
		bit[idx][1].update(dis[cur[idx]-1][x],d);
		update(Fa[idx],x,d);
	}
}
void query(int idx,int x,int k){
	int d=max(-1,min(bit[idx][0].n-1,k-dis[cur[idx]][x]));
	ans+=bit[idx][0].que(d);
	if(Fa[idx]){
		d=max(-1,min(bit[idx][1].n-1,k-dis[cur[idx]-1][x]));
		ans-=bit[idx][1].que(d);
		query(Fa[idx],x,k);
	}
}
int main() {
	while(scanf("%d %d",&N,&Q)!=EOF){
		for(int i=1;i<=N;i++){
			scanf("%d",&rec[i]);
		}
		int x,y;
		for(int i=0;i<=N;i++){
			head[i]=-1;
			vis[i]=0;
		}
		//memset(head,-1,sizeof(head));
		//memset(vis,0,sizeof(vis));
		cnt=pl=tot=0;
		for(int i=1;i<N;i++){
			scanf("%d %d",&x,&y);
			add_edge(x, y);
			add_edge(y, x);
		}
		f[0]=inf;
		cur[0]=0;
		ids[0]=0;
		root=0;
		S=N;
		getroot(1,0);
		solve(root,0);
		char ch[3];
		for(int i=0;i<Q;i++){
			scanf("%s %d %d",ch,&x,&y);
			if(ch[0]=='!'){
				update(ids[x],x,y-rec[x]);
				rec[x]=y;
			}else{
				ans=0;
				query(ids[x],x,y);
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}