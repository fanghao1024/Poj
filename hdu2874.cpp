#include<stdio.h>
#include<string.h>

const int max_n=10010;
int N,M,C;

struct Edge{
	int to,next;
	int val;
}E[max_n<<1],QE[2000010];
int par[max_n];
int dis[max_n];
int head[max_n];
int qhead[max_n];
int vis[max_n];
int ce,qe;

void init(){
	memset(head,-1,sizeof(head));
	memset(qhead,-1,sizeof(qhead));
	memset(par,0,sizeof(par));
	memset(dis,0,sizeof(dis));
	memset(vis,0,sizeof(vis));
	ce=qe=0;
}
void add1(int x,int y,int d){
	E[ce].to=y;
	E[ce].val=d;
	E[ce].next=head[x];
	head[x]=ce++;
}
void add2(int x,int y){
	QE[qe].to=y;
	QE[qe].next=qhead[x];
	QE[qe].val=-1;
	qhead[x]=qe++;
	
}
int find(int x){
	if(x!=par[x]){
		par[x]=find(par[x]);
	}
	return par[x];
}
void tarjan(int u,int root){
	par[u]=u;
	vis[u]=root;
	for(int i=head[u];i!=-1;i=E[i].next){
		int v=E[i].to;
		if(!vis[v]){
			dis[v]=dis[u]+E[i].val;
			tarjan(v,root);
			par[v]=u;
		}
	}
	for(int i=qhead[u];i!=-1;i=QE[i].next){
		int v=QE[i].to;
		
		if(vis[v]&&vis[u]==vis[v]){
			
			QE[i].val=dis[v]+dis[u]-2*dis[find(v)];
			QE[i^1].val=QE[i].val;
		}
	}
}

int main(){
	
	while(scanf("%d %d %d",&N,&M,&C)!=EOF){
		init();
		int x,y,d;
		for(int i=0;i<M;i++){
			scanf("%d %d %d",&x,&y,&d);
			add1(x,y,d);
			add1(y,x,d);
		}
		for(int i=0;i<C;i++){
			scanf("%d %d",&x,&y);
			add2(x,y);
			add2(y,x);
		}
		for(int i=1;i<=N;i++){
			
			if(!vis[i]){
				tarjan(i,i);
			}
		}
		for(int i=0;i<C;i++){
			if(QE[2*i].val==-1){
				printf("Not connected\n");
			}else{
				printf("%d\n",QE[2*i].val);
			}
		}
	}
	return 0;
}
