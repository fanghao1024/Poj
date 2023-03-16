#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e5+10;

int N,M,R,P,cnt,num;
int dep[max_n],siz[max_n],son[max_n],fa[max_n],id[max_n],val[max_n],head[max_n],top[max_n],toid[max_n];
int tree[max_n<<2],tag[max_n<<2];
struct Edge{
	int to,next;
}edge[max_n<<1];
int read(){
	int num=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		num*=10;
		num+=ch-'0';
		ch=getchar();
	}
	return num;
}
void update_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].next=head[x];
	head[x]=cnt++;
}
void init(){
	memset(head,-1,sizeof(head));
	memset(son,0,sizeof(son));
	cnt=0;
	num=0;
}
void dfs1(int u,int father){
	dep[u]=dep[father]+1;
	fa[u]=father;
	siz[u]=1;
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].to;
		if(v==father) continue;
		dfs1(v,u);
		if(!son[u]||siz[son[u]]<siz[v]) son[u]=v;
		siz[u]+=siz[v];
	}
}
void dfs2(int u,int t){
	top[u]=t;
	id[u]=++num;
	toid[num]=u;
	if(!son[u]) return ;
	dfs2(son[u],t);
	for(int i=head[u];i!=-1;i=edge[i].next){
		int v=edge[i].to;
		if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
	}
}
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void add_tag(int p,int pl,int pr,int d){
	tag[p]+=d;
	tree[p]+=(pr-pl+1)*d;
	tree[p]%=P;
}
void push_up(int p){
	tree[p]=tree[ls(p)]+tree[rs(p)];
	tree[p]%=P;
}
void build(int p,int pl,int pr){
	tag[p]=0;
	if(pl==pr){
		tree[p]=val[toid[pl]]%P;
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p);
}
void push_down(int p,int pl,int pr){
	if(tag[p]){
		int mid=(pl+pr)>>1;
		//tag[ls(p)]+=tag[p];tree[ls(p)]+=(mid-pl+1)*tag[p];tree[ls(p)]%=P;
		//tag[rs(p)]+=tag[p];tree[rs(p)]+=(pr-mid)*tag[p];tree[rs(p)]%=P;
		add_tag(ls(p),pl,mid,tag[p]);
		add_tag(rs(p),mid+1,pr,tag[p]);
		tag[p]=0;
	}
}

void update(int l,int r,int v,int p,int pl,int pr){
	if(l<=pl&&pr<=r){
		tag[p]+=v;
		tree[p]+=(pr-pl+1)*v;
		tree[p]%=P;
		return ;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	if(l<=mid) update(l,r,v,ls(p),pl,mid);
	if(r>mid) update(l,r,v,rs(p),mid+1,pr);
	push_up(p);
}

int query(int l,int r,int p,int pl,int pr){
	if(l<=pl&&pr<=r){
		return tree[p]%=P;
	}
	push_down(p,pl,pr);
	int mid=(pl+pr)>>1;
	int res=0;
	if(l<=mid) res+=query(l,r,ls(p),pl,mid);
	if(r>mid) res+=query(l,r,rs(p),mid+1,pr);
	res%=P;
	return res;
}

void update_range(int x,int y,int z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		update(id[top[x]],id[x],z,1,1,num);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	update(id[x],id[y],z,1,1,num);
}
void query_range(int x,int y){
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res+=query(id[top[x]],id[x],1,1,num);
		res%=P;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	res+=query(id[x],id[y],1,1,num);
	printf("%d\n",res%P);
}

void update_subtree(int x,int z){
	update(id[x],id[x]+siz[x]-1,z,1,1,num);
}
void query_subtree(int x){
	printf("%d\n",query(id[x],id[x]+siz[x]-1,1,1,num)%P);
  }
int main(){
	scanf("%d %d %d %d",&N,&M,&R,&P);
	//N=read();M=read();R=read();P=read();
	init();
	for(int i=1;i<=N;i++) //val[i]=read();
		scanf("%d",&val[i]);
	int ops,x,y,z;
	for(int i=1;i<N;i++){
		scanf("%d %d",&x,&y);
		//x=read();y=read();
		update_edge(x,y);
		update_edge(y,x);
	}
	dfs1(R,0);
	dfs2(R,R);
	build(1,1,num);

	while(M--){
		//ops=read();
		scanf("%d",&ops);
		switch (ops) {
		case 1:
			//x=read();y=read();z=read();
			scanf("%d %d %d",&x,&y,&z);
			update_range(x,y,z);
			break;
		case 2:
			//x=read();y=read();
			scanf("%d %d",&x,&y);
			query_range(x,y);
			break;
		case 3:
			//x=read();z=read();
			scanf("%d %d",&x,&z);
			update_subtree(x,z);
			break;
		case 4:
			//x=read();
			scanf("%d",&x);
			query_subtree(x);
			break;
		}
	}
	return 0;
}
