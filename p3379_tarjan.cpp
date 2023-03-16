#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=5e5+10;
int N,M,S;
int head[max_n],qhead[max_n],cnt,qcnt,par[max_n],ans[max_n];
bool vis[max_n];
struct Edge{
	int to,nxt;
	int id;
}edge[max_n<<1],qedge[max_n<<1];

void init(){
	memset(head,-1,sizeof(head));
	memset(qhead,-1,sizeof(qhead));
	memset(vis,0,sizeof(vis));
	cnt=qcnt=0;
	for(int i=0;i<=N;i++) par[i]=i;
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void add_qedge(int x,int y,int z){
	qedge[qcnt].to=y;
	qedge[qcnt].nxt=qhead[x];
	qedge[qcnt].id=z;
	qhead[x]=qcnt++;
}
int find(int x){
	if(x!=par[x]){
		par[x]=find(par[x]);
	}
	return par[x];
}
void unite(int x,int y){
	int rx=find(x);
	int ry=find(y);
	if(rx!=ry){
		par[rx]=ry;
	}
}
void tarjan(int u){
	vis[u]=1;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(!vis[v]){
			tarjan(v);
			par[v]=u;
		}
	}
	for(int i=qhead[u];i!=-1;i=qedge[i].nxt){
		int v=qedge[i].to;
		if(vis[v]){
			ans[qedge[i].id]=find(v);
		}
	}
}
int main(){
	scanf("%d %d %d",&N,&M,&S);
	int x,y;
	init();
	for(int i=1;i<N;i++){
		scanf("%d %d",&x,&y);
		add_edge(x,y);add_edge(y,x);
	}
	for(int i=1;i<=M;i++){
		scanf("%d %d",&x,&y);
		add_qedge(x,y,i);
		add_qedge(y,x,i);
	}
	tarjan(S);
	for(int i=1;i<=M;i++) printf("%d\n",ans[i]);
	return 0;
}
