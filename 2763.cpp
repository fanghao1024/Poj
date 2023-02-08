#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=100010;
int N,Q,S,cnt,num;
int head[max_n];
int fa[max_n],son[max_n],dep[max_n],siz[max_n],id[max_n],top[max_n];
int w[max_n],new_w[max_n];
int tree[max_n<<2],tag[max_n<<2];

struct Edge{
	int to,w;
	int nxt;
}edge[max_n<<1];
void init(){
	memset(head,-1,sizeof(head));
	memset(son,0,sizeof(son));
	cnt=num=0;
	siz[0]=dep[0]=fa[0]=0;
}
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void add_tag(int p,int pl,int pr,int d){
	tag[p]+=d;
	tree[p]+=d*(pr-pl+1);
}
void push_up(int p){
	tree[p]=tree[ls(p)]+tree[rs(p)];
}
void push_down(int p,int pl,int pr){
	if(tag[p]){
		int mid=(pl+pr)>>1;
		add_tag(ls(p),pl,mid,tag[p]);
		add_tag(rs(p),mid+1,pr,tag[p]);
		tag[p]=0;
	}
}
void build(int p,int pl,int pr){
	tag[p]=0;
	if(pl==pr){
		tree[p]=new_w[pl];
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p);
}
void update(int L,int R,int p,int pl,int pr,int d){
	if(L<=pl&&pr<=R){
		add_tag(p,pl,pr,d);
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(L<=mid) update(L,R,ls(p),pl,mid,d);
	if(R>mid) update(L,R,rs(p),mid+1,pr,d);
	push_up(p);
}
int query(int L,int R,int p,int pl,int pr){
	if(L<=pl&&pr<=R) return tree[p];
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	int ans=0;
	if(L<=mid) ans+=query(L,R,ls(p),pl,mid);
	if(R>mid) ans+=query(L,R,rs(p),mid+1,pr);
	return ans;
}
void add_edge(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=w;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void dfs1(int u,int father){
	siz[u]=1;
	dep[u]=dep[father]+1;
	fa[u]=father;
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
		if(v!=fa[x]&&v!=son[x]){
			dfs2(v,v);
		}
	}
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
void update_range(int x,int y){
	int edge1=2*(x-1);
	int edge2=edge1^1;
	int v=dep[edge[edge1].to]>dep[edge[edge2].to]?edge[edge1].to:edge[edge2].to;
	update(id[v],id[v],1,1,N,y-new_w[id[v]]);
	new_w[id[v]]=y;
}
int main(){
	scanf("%d %d %d",&N,&Q,&S);
	init();
	int x,y,weight;
	for(int i=1;i<N;i++){
		scanf("%d %d %d",&x,&y,&weight);
		add_edge(x,y,weight);
		add_edge(y,x,weight);
	}
	w[S]=0;
	dfs1(S,0);
	dfs2(S,S);
	build(1,1,N);
	for(int i=1;i<=Q;i++){
		scanf("%d",&weight);
		if(weight==0){
			scanf("%d",&x);
			printf("%d\n",query_range(S,x));
			S=x;
		}else{
			scanf("%d %d",&x,&y);
			update_range(x,y);
		}
	}
	return 0;
}
