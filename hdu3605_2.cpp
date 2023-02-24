#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=2050;
const int inf=0x3f3f3f3f;
int person[max_n];
int plaent[12];
int head[max_n];
int cnt,N,M;
int dep[max_n],g[max_n],now[max_n],pre[max_n*100];
struct Edge{
	int to,nxt;
	int cap,flow;
}edge[max_n*max_n];
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
void init(){
	memset(head,-1,sizeof(head));
	memset(person,0,sizeof(person));
	cnt=0;
}
void bfs(int t){
	memset(dep,0,sizeof(dep));
	memset(g,0,sizeof(g));
	queue<int> q;
	q.push(t);
	dep[t]=1;
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
	int ans=0;
	int u=s;
	int d;
	memcpy(now,head,sizeof(head));
	while(dep[s]<=n){
		if(u==s) d=inf;
		int i=now[u];
		for(;i!=-1;i=edge[i].nxt){
			int v=edge[i].to;//printf("%d %d %d %d\n",v,dep[v],edge[i].cap,edge[i].flow);
			if(dep[v]+1==dep[u]&&edge[i].cap>edge[i].flow){//printf("####%d\n",v);
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
					d=inf;
				}
				break;
			}
		}
		if(i==-1){
			if(!--g[dep[u]]) break;
			int mindep=n+5;
			for(int j=head[u];j!=-1;j=edge[j].nxt){
				int v=edge[j].to;
				if(edge[j].cap>edge[j].flow&&dep[v]<mindep) mindep=dep[v];
			}
			dep[u]=mindep+1;
			now[u]=head[u];
			g[dep[u]]++;
			if(u!=s) u=edge[pre[u]^1].to;
		}
	}
	return ans;
}
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		init();
		for(int i=0;i<N;i++){
			int sum=0,k;
			for(int i=0;i<M;i++){
				scanf("%d",&k);
				sum<<=1;
				sum+=k;
			}
			person[sum]++;
		}
		for(int i=0;i<M;i++){
			scanf("%d",&plaent[i]);
		}
		int s=1023+M+1,t=1023+M+2;
		for(int i=0;i<1024;i++){
			if(person[i]){
				adde(s,i,person[i]);
				for(int j=0;j<M;j++){
					if(i&(1<<j)) adde(i,1024+j,person[i]); 
				}
			}
		}
		for(int i=0;i<M;i++) adde(1024+i,t,plaent[i]);
		int ans=isap(s,t,t+1);//printf("~~%d\n",ans);
		if(ans>=N) printf("YES\n");
		else printf("No\n");
	}
	return 0;
}
