#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=30010;
int head[max_n];
struct Edge{
	int to;
	int nxt;
}edge[max_n<<1];
int N,Q,cnt,num,ansMax,ansSum;
int w[max_n],new_w[max_n];
int fa[max_n],son[max_n],dep[max_n],siz[max_n],id[max_n],top[max_n];
int maxtree[max_n<<2],sumtree[max_n<<2];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}

void init(){
	memset(head,-1,sizeof(head));
	memset(son,0,sizeof(son));
	cnt=num=0;
	siz[0]=dep[0]=fa[0]=0;
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void push_up(int p){
	maxtree[p]=max(maxtree[ls(p)],maxtree[rs(p)]);
	sumtree[p]=sumtree[ls(p)]+sumtree[rs(p)];
}
void build(int p,int pl,int pr){
	if(pl==pr){
		maxtree[p]=sumtree[p]=new_w[pl];
		return ;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	push_up(p);
}
void update(int x,int p,int pl,int pr,int d){
	if(x<pl||x>pr) return;
	if(pl==x&&pr==x) {maxtree[p]=sumtree[p]=d;return;}
	int mid=(pl+pr)>>1;
	if(x<=mid) update(x,ls(p),pl,mid,d);
	if(x>mid) update(x,rs(p),mid+1,pr,d);
	push_up(p);
}
void query(int L,int R,int p,int pl,int pr){
	if(L<=pl&&pr<=R){
		ansMax=max(ansMax,maxtree[p]);
		ansSum+=sumtree[p];
		return ;
	}
	int mid=(pl+pr)>>1;
	if(L<=mid) query(L,R,ls(p),pl,mid);
	if(R>mid) query(L,R,rs(p),mid+1,pr);
}
void dfs1(int u,int father){
	siz[u]=1;
	dep[u]=dep[father]+1;
	fa[u]=father;
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
void query_range(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		query(id[top[x]],id[x],1,1,N);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	query(id[x],id[y],1,1,N);
}
int main(){
	scanf("%d",&N);
	int x,y;
	init();
	for(int i=1;i<N;i++){
		scanf("%d %d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	for(int i=1;i<=N;i++) scanf("%d",w+i);
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,N);
	char s[20];
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++){
		scanf("%s %d %d",s,&x,&y);
		if(s[1]=='H'){
			int xx=id[x];
			update(xx,1,1,N,y);
		}else{
			
			ansMax=-0x3f3f3f3f;
			ansSum=0;
			query_range(x,y);
			if(s[1]=='M') printf("%d\n",ansMax);
			else printf("%d\n",ansSum);
		}
	}
	return 0;
}
