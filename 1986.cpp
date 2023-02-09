#include <iostream>
#include<stdio.h>
#include<string.h>

using namespace std;

int N,M;
const int max_n=80005;
int head[max_n];
int qhead[max_n];
int par[max_n];
int dis[max_n];
struct Edge{
	int to,nxt;
	int value;
}E[max_n],QE[max_n];
int cnt,tot;
bool vis[max_n];
void init(){
	memset(head,-1,sizeof(head));
	memset(qhead,-1,sizeof(qhead));
	//for(int i=1;i<=N;i++){
	//	par[i]=i;
	//}
	memset(par,0,sizeof(par));
	memset(E, 0, sizeof(E));
	memset(QE,0,sizeof(QE));
	memset(vis,0,sizeof(vis));
	memset(dis,0,sizeof(dis));
	cnt=tot=0;
}

void add1(int x,int y,int d){
	E[cnt].to=y;
	E[cnt].value=d;
	E[cnt].nxt=head[x];
	head[x]=cnt++;
}

void add2(int x,int y){
	QE[tot].to=y;
	QE[tot].nxt=qhead[x];
	qhead[x]=tot++;
}
int find(int x){
	if(x!=par[x]){
		par[x]=find(par[x]);
	}
	return par[x];
}
void tarjan(int u){
	vis[u]=1;
	par[u]=u;
	for(int i=head[u];i!=-1;i=E[i].nxt){
		int v=E[i].to;
		if(!vis[v]){
			dis[v]=dis[u]+E[i].value;
			tarjan(v);
			par[v]=u;
		}
	}
	for(int i=qhead[u];i!=-1;i=QE[i].nxt){
		int v=QE[i].to;
		if(vis[v]){
			QE[i].value=dis[v]+dis[u]-2*dis[find(v)];
			QE[i^1].value=QE[i].value;		
		}
	}
}
int main() {
	init();
	
	while(scanf("%d %d",&N,&M)!=EOF){
		int x,y,d;
		char ch;
		for(int i=0;i<M;i++){
			scanf("%d%d%d %c",&x,&y,&d,&ch);
			add1(x,y,d);
			add1(y,x,d);
		}
		int K;
		scanf("%d",&K);
		for(int i=0;i<K;i++){
			scanf("%d %d",&x,&y);
			add2(x,y);
			add2(y,x);
		}
		tarjan(1);
		for(int i=0;i<K;i++){
			printf("%d\n",QE[i*2].value);
		}
	}
	return 0;
}