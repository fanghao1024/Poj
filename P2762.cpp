#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;

const int max_n=110;
const int inf=0x3f3f3f3f;

int head[max_n],dep[max_n],cnt;
int N,M,s,t,sum;
struct Edge{
	int to,nxt;
	int cap,flow;
}edge[(max_n*max_n)<<1];
void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
	s=0;
	t=N+M+1;
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
		adde(s,i,fee);
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
		adde(i+M,t,fee);
	}
	
}
bool bfs(int s,int t){
	memset(dep,0,sizeof(dep));
	queue<int> q;
	dep[s]=1;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(!dep[v]&&edge[i].cap>edge[i].flow){
				dep[v]=dep[u]+1;
				q.push(v);
				if(v==t) return true;
			}
		}
	}
	return false;
}
int dfs(int u,int flow,int t){
	if(u==t) return flow;
	int rest=flow;
	for(int i=head[u];i!=-1&&rest;i=edge[i].nxt){
		int v=edge[i].to;
		if(dep[v]==dep[u]+1&&edge[i].cap>edge[i].flow){
			int k=dfs(v,min(rest,edge[i].cap-edge[i].flow),t);
			if(!k) dep[v]=0;
			edge[i].flow+=k;
			edge[i^1].flow-=k;
			rest-=k;
		}
	}
	return flow-rest;
}
int dinic(int s,int t){
	int maxflow=0;
	while(bfs(s,t)) maxflow+=dfs(s,inf,t);
	return maxflow;
}
void Print(){
	for(int i=1;i<=M;i++){
		if(dep[i]) printf("%d ",i);
	}
	printf("\n");
	for(int i=1;i<=N;i++){
		if(dep[i+M]) printf("%d ",i);
	}
	printf("\n");
}
int main(){	
	readin();
	int ans=sum-dinic(s,t);
	Print();
	printf("%d\n",ans);
	return 0;
}
