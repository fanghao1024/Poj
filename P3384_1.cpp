#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

typedef int ll;
const int max_n=100010;
int N,M,R,P,cnt,num;
int head[max_n];
int w[max_n],new_w[max_n];
int fa[max_n],son[max_n],dep[max_n],siz[max_n],top[max_n],id[max_n];
struct Edge{
	int to,nxt;
}edge[max_n<<1];
int tree[max_n<<2],tag[max_n<<2];

int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void add_tag(int p,int pl,int pr,int d){
	tag[p]+=d;
	tree[p]+=(pr-pl+1)*d;
	tree[p]%=P;
}
void push_up(int p){
	tree[p]=(tree[ls(p)]+tree[rs(p)])%P;
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
		tree[p]=new_w[pl];tree[p]%=P;
		return;
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
	if(L<=pl&&pr<=R) return tree[p]%=P;
	push_down(p,pl,pr);
	int ans=0;
	int mid=(pl+pr)>>1;
	if(L<=mid) ans+=query(L,R,ls(p),pl,mid);
	if(R>mid) ans+=query(L,R,rs(p),mid+1,pr);
	ans%=P;
	return ans;
}
 /*
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void add_tag(int p,int pl,int pr,int d){
	tag[p]+=d;
	tree[p]+=(pr-pl+1)*d;
	tree[p]%=P;
}
void push_up(int p){
	tree[p]=(tree[ls(p)]+tree[rs(p)])%P;
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
		tree[p]%=P;
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p);
}
void update(int L,int R,int p,int pl,int pr,int d){
	if(L<=pl&&pr<=R){
		add_tag(p,pl,pr,d);return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(L<=mid) update(L,R,ls(p),pl,mid,d);
	if(R>mid) update(L,R,rs(p),mid+1,pr,d);
	push_up(p);
}
ll query(int L,int R,int p,int pl,int pr){
	if(L<=pl&&pr<=R){
		return tree[p]%=P;
	}
	push_down(p,pl,pr);
	ll ans=0;
	int mid=(pl+pr)>>1;
	if(L<=mid) ans+=query(L,R,ls(p),pl,mid);
	if(R>mid) ans+=query(L,R,rs(p),mid+1,pr);
	ans%=P;
	return ans;
}*/
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void init(){
	memset(head,-1,sizeof(head));
	memset(son,0,sizeof(son));
	cnt=num=0;
	fa[0]=0;
	dep[0]=0;
	siz[0]=0;
}
void dfs1(int u,int father){
	fa[u]=father;
	dep[u]=dep[father]+1;
	siz[u]=1;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=father){
			dfs1(v,u);
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
void update_range(int x,int y,int z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		update(id[top[x]],id[x],1,1,N,z);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	update(id[x],id[y],1,1,N,z);
}
void query_range(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans+=query(id[top[x]],id[x],1,1,N);
		ans%=P;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	ans+=query(id[x],id[y],1,1,N);
	ans%=P;
	printf("%d\n",ans);
}
void update_subtree(int x,int y){
	update(id[x],id[x]+siz[x]-1,1,1,N,y);
}
void query_subtree(int x){
	printf("%d\n",query(id[x],id[x]+siz[x]-1,1,1,N));
}
int main(){
	scanf("%d %d %d %d",&N,&M,&R,&P);
	init();
	for(int i=1;i<=N;i++) scanf("%d",w+i);
	int x,y;
	for(int i=1;i<N;i++){
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs1(R,0);
	dfs2(R,R);
	build(1,1,N);
	int u,z;

	for(int i=1;i<=M;i++){
		scanf("%d",&u);
		switch(u){
		case 1:scanf("%d %d %d",&x,&y,&z);update_range(x,y,z);break;
		case 2:scanf("%d %d",&x,&y);query_range(x,y);break;
		case 3:scanf("%d %d",&x,&y);update_subtree(x,y);break;
		case 4:scanf("%d",&x);query_subtree(x);break;
		}
	}
	return 0;
}
