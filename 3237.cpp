#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=10010;
int T,N,cnt,num,maxAns;
int head[max_n];
int fa[max_n],son[max_n],siz[max_n],dep[max_n],top[max_n],id[max_n];
int w[max_n],new_w[max_n];
int maxtree[max_n<<2],mintree[max_n<<2];
int tag[max_n<<2];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
struct Edge{
	int to,w;
	int nxt;
}edge[max_n<<1];
void init(){
	memset(head,-1,sizeof(head));
	memset(son,0,sizeof(son));
	cnt=num=0;
	fa[0]=siz[0]=dep[0]=0;
}
void add_edge(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=w;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void push_down(int p,int pl,int pr){
	if(pl==pr) return ;
	if(tag[p]){
		maxtree[ls(p)]=-maxtree[ls(p)];
		mintree[ls(p)]=-mintree[ls(p)];
		swap(maxtree[ls(p)],mintree[ls(p)]);
		maxtree[rs(p)] = -maxtree[rs(p)];
		mintree[rs(p)] = -mintree[rs(p)];
		swap(maxtree[rs(p)], mintree[rs(p)]);
		tag[ls(p)]^=1;
		tag[rs[p]]^=1;
		tag[p]=0;
	}
}
void push_up(int p){
	maxtree[p]=max(maxtree[ls(p)],maxtree[rs(p)]);
	mintree[p]=min(mintree[ls(p)],mintree[rs(p)]);
}
void build(int p,int pl,int pr){
	addtag[p]=0;
	multag[p]=1;
	if(pl==pr){
		mintree[p]=maxtree[p]=new_w[pl];
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p);
}
void update1(int k,int p,int pl,int pr,int d){
	if(k<pl||k>pr) return ;
	if(k==pl&&k==pr){
		maxtree[p]=mintree[p]=d;
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	update1(k,ls(p),pl,mid,d);
	update1(k,rs(p),mid+1,pr,d);
	push_up(p);
}
void update2(int L,int R,int p,int pl,int pr){
	if(L<=pl&&pr<=R){
		maxtree[p] = -maxtree[p];
		mintree[p] = -mintree[p];
		swap(maxtree[p], mintree[p]);
		tag[p]^=1;
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(L<=mid) update2(L,R,ls(p),pl,mid);
	if(R>mid) update2(L,R,rs(p),mid+1,pr);
	push_up(p);
}
void query(int L,int R,int p,int pl,int pr){
	if(L<=pl&&pr<=pr){
		maxAns=max(maxAns,maxtree[p]);
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(L<=mid) query(L,R,ls(p),pl,mid);
	if(R>mid) query(L,R,rs(p),mid+1,pr);
}
int ask(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]){
			swap(x,y);
		}
		query(id[top[x]],id[x],1,1,N);
		x=fa[top[x]];
	}
	if(dep[x]==dep[y]) return ;
	if(dep[x]>dep[y]) swap(x,y);
	query(id[x]+1,id[y],1,1,N);
}
void NEGATE(int x, int y)
{
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		update2(id[top[x]], id[x], 1, 1, N);
		x = fa[top[x]];
	}
	if (dep[x] == dep[y])
		return;
	if (dep[x] > dep[y])
		swap(x, y);
	update2(id[x] + 1, id[y], 1, 1, N);
}
void dfs1(int u,int father){
	fa[u]=father;
	dep[u]=dep[father]+1;
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
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		int x,y,z;
		init();
		for(int i=1;i<N;i++){
			scanf("%d %d %d",&x,&y,&z);
			add_edge(x,y,z);
			add_edge(y,x,z);
		}
		w[1]=0;
		dfs1(1,0);
		dfs2(1,1);
		build(1,1,N);
		char s[20];
		while(scanf("%s",s)){
			if(s[0]=='D') break;
			scanf("%d %d",&x,&y);
			if(s[0]=='C'){
				update1()
			}else{
				if(s[0]=='N'){

				}else{

				}
			}
		}
	}
	return 0;
}
