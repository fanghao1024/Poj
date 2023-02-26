#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;

const int max_n=110;
const int inf=0x3f3f3f3f;

int head[max_n],dep[max_n],g[max_n],pre[max_n],now[max_n],cnt;
bool vis[max_n];
int N,M,S,T,sum;
struct Edge{
	int to,nxt;
	int cap,flow;
}edge[(max_n*max_n)<<1];
void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
	S=0;
	T=N+M+1;
	sum=0;
}
void add_edge(int x,int y,int c){
	edge[cnt].to=y;
	edge[cnt].cap=c;
	edge[cnt].flow=0;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void adde(int x,int y,int c){
	add_edge(x,y,c);
	add_edge(y,x,0);
}


void readin(){
	scanf("%d %d",&M,&N);
	init();
	for(int i=1;i<=M;i++){
		int fee;
		scanf("%d",&fee);
		adde(S,i,fee);
		sum+=fee;
		
		char tools[10000];
		memset(tools,0,sizeof tools);
		cin.getline(tools,10000);
		int ulen=0,tool;
		while (sscanf(tools+ulen,"%d",&tool)==1)//之前已经用scanf读完了赞助商同意支付该实验的费用
		{//tool是该实验所需仪器的其中一个      
			//这一行，你可以将读进来的编号进行储存、处理，如连边。
			adde(i,tool+M,inf);
			if (tool==0) 
				ulen++;
			else {
				while (tool) {
					tool/=10;
					ulen++;
				}
			}
			ulen++;
		}
	}
	for(int i=1;i<=N;i++){
		int fee;
		scanf("%d",&fee);
		adde(i+M,T,fee);
	}
	
}
void bfs(int t){
	memset(g,0,sizeof(g));
	memset(dep,0,sizeof(dep));
	dep[t]=1;
	queue<int> q;
	q.push(t);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		g[dep[u]]++;
		for(int i=head[u];i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(!dep[v]){
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
}
int isap(int s,int t,int n){
	bfs(t);
	int u=s;
	int ans=0;
	int d;
	memcpy(now,head,sizeof(head));
	while(dep[s]<=n){
		if(u==s) d=inf;
		int i=now[u];
		for(;i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(dep[v]==dep[u]-1&&edge[i].cap>edge[i].flow){
				d=min(d,edge[i].cap-edge[i].flow);
				pre[v]=i;
				now[u]=i;
				u=v;
				if(u==t){
					while(u!=s){
						int e=pre[u];
						edge[e].flow+=d;
						edge[e^1].flow-=d;
						u=edge[e^1].to;
					}
					ans+=d;
				}
				break;
			}
		}
		if(i==-1){
			if(!--g[dep[u]]) break;
			int mindep=n+5;
			for(int j=head[u];j!=-1;j=edge[j].nxt){
				int v=edge[j].to;
				if(edge[j].cap>edge[j].flow&&mindep>dep[v]) mindep=dep[v]; 
			}
			dep[u]=mindep+1;
			g[dep[u]]++;
			now[u]=head[u];
			if(u!=s) u=edge[pre[u]^1].to;
		}
	}
	return ans;
}
void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(edge[i].cap>edge[i].flow){
			dfs(v);
		}
	}
}
void Print(){
	memset(vis,0,sizeof(vis));
	dfs(S);
	for(int i=1;i<=M;i++) if(vis[i]) printf("%d ",i);
	printf("\n");
	for(int i=1;i<=N;i++) if(vis[i+M]) printf("%d ",i);
	printf("\n");
}
int main(){	
	readin();
	int ans=sum-isap(S,T,T+1);
	Print();
	printf("%d\n",ans);
	return 0;
}
