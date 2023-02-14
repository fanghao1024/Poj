#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=100005;
int N,M,cnt,num;
int head[max_n];
struct Edge{
	int to,w;
	int nxt;
}edge[max_n<<1];
int fa[max_n],siz[max_n],dep[max_n],son[max_n],top[max_n],id[max_n];
int w[max_n],new_w[max_n];
int tree[max_n<<2];

void add_edge(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=w;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void init(){
	memset(head,-1,sizeof(head));
	memset(son,0,sizeof(son));
	cnt=num=0;
	dep[0]=0;
}
void dfs1(int u,int father){
	dep[u]=dep[father]+1;
	fa[u]=father;
	siz[u]=1;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=father){
			dfs1(v,u);
			w[v]=edge[i].w;
			siz[u]+=siz[v];
			if(!son[u]||siz[son[u]]<siz[v]) son[u]=v;
		}
	}
}
void dfs2(int x,int topx){
	id[x]=++num;
	new_w[num]=w[x];
	top[x]=topx;
	if(!son[x]) return ;
	dfs2(son[x],topx);
	for(int i=head[x];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=fa[x]&&v!=son[x]) dfs2(v,v);
	}
}
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void pushup(int p){
	tree[p]=tree[ls(p)]+tree[rs(p)];
}
void build(int p,int pl,int pr){
	if(pl==pr){
		tree[p]=new_w[pl];
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	pushup(p);
}
int query(int L,int R,int p,int pl,int pr){
	if(L<=pl&&pr<=R) return tree[p];
	int mid=(pl+pr)>>1;
	int res=0;
	if(L<=mid) res+=query(L,R,ls(p),pl,mid);
	if(R>mid) res+=query(L,R,rs(p),mid+1,R);
	return res;
}
int query_range(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans+=query(id[top[x]],id[x],1,1,N);
		x=fa[top[x]];
	}
	if(dep[x]==dep[y]) return ans;
	if(dep[x]>dep[y]) swap(x,y);
	ans+=query(id[x]+1,id[y],1,1,N);
	return ans;
}
int main(){
	int x,y,d;
	char ch;
	while(scanf("%d %d",&N,&M)!=EOF){
		init();
		for(int i=1;i<=M;i++){
			scanf("%d %d %d %c",&x,&y,&d,&ch);
			add_edge(x,y,d);
			add_edge(y,x,d);
		}
		w[1]=0;
		dfs1(1,0);
		dfs2(1,1);
		scanf("%d",&d);
		build(1,1,N);
		while(d--){
			scanf("%d %d",&x,&y);
			printf("%d\n",query_range(x,y));
		}
	}
	return 0;
}
