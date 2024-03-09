#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_p=13;
const int max_n=55;
const int inf=0x3f3f3f3f;

int info[max_n],input[max_n][max_p],output[max_n][max_p];
int P,N,cnt;
int head[max_n<<1],dep[max_n<<1],g[max_n<<1],pre[(max_n*max_n)<<2],now[max_n<<1];
bool vis[max_n<<1][max_n<<1];
struct edgedge{
	int to,nxt;
	int cap,flow;
}edge[(max_n*max_n)<<2];
void init(){
	memset(head,-1,sizeof(head));
	memset(vis,0,sizeof(vis));
	cnt=0;
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
bool checkInputZero(int i){
	for(int j=0;j<P;j++) if(input[i][j]) return false;
	return true;
}
bool checkOutputOne(int i){
	for(int j=0;j<P;j++) if(output[i][j]!=1) return false;
	return true;
}
bool check(int i,int j){
	for(int k=0;k<P;k++){
		if(input[j][k]==2||output[i][k]==input[j][k]) continue;
		return false;
	}
	return true;
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
			if(!dep[v]) dep[v]=dep[u]+1,q.push(v);
		}
	}
}
int isap(int s,int t,int n){
	bfs(t);
	int ans=0;
	int u=s,d;
	memcpy(now,head,sizeof(head));
	while(dep[s]<=n){
		if(u==s) d=inf;
		int i=now[u];
		for(;i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(dep[v]+1==dep[u]&&edge[i].cap>edge[i].flow){
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
				if(edge[j].cap>edge[j].flow&&dep[v]<mindep) mindep=dep[v];
			}
			dep[u]=mindep+1;
			g[dep[u]]++;
			now[u]=head[u];
			if(u!=s) u=edge[pre[u]^1].to;
		}
	}
	return ans;
}
void set_h(int t,int n){//±ê¸ß 
	queue<int> q;
	memset(dep,-1,sizeof(dep));
	memset(g,0,sizeof(g));
	dep[t]=0;
	q.push(t);
	while(!q.empty()){
		int u=q.front();q.pop();
		++g[dep[u]];//¸ß¶ÈÎªh[u]µÄ½Úµã¸öÊý
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].to;
			if(dep[v]==-1){
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
}
int ISAP(int s,int t,int n){
	set_h(t,n);
	int ans=0,u=s,d;
	while(dep[s]<n){
		int i=head[u];
		if(u==s)
			d=inf;
		for(;~i;i=edge[i].nxt){
			int v=edge[i].to;
			if(edge[i].cap>edge[i].flow&&dep[u]==dep[v]+1){
				u=v;
				pre[v]=i;
				d=min(d,edge[i].cap-edge[i].flow);
				if(u==t){
					while(u!=s){
						int j=pre[u];
						edge[j].flow+=d;
						edge[j^1].flow-=d;
						u=edge[j^1].to;
					}
					ans+=d;
					d=inf;
				}
				break;
			}
		}
		if(i==-1){
			if(--g[dep[u]]==0)
				break;
			int hmin=n-1;
			for(int j=head[u];~j;j=edge[j].nxt)
				if(edge[j].cap>edge[j].flow)
					hmin=min(hmin,dep[edge[j].to]);
			dep[u]=hmin+1;
			++g[dep[u]];
			if(u!=s)
				u=edge[pre[u]^1].to;
		}
	}
	return ans;
}

bool check1(int x,int y){
	return x==y||y==2;
}

bool ck1(int d){ //Ã»ÓÐ1
	for(int i=1;i<=P;i++)
		if(input[d][i]==1) return false;
	return true;
}

bool ck2(int d){ //È«1
	for(int i=1;i<=P;i++)
		if(output[d][i]!=1) return false;
	return true;
}

int main(){
	while(scanf("%d %d",&P,&N)!=EOF){
		/*
		init();
		int s=0,t=2*N+1;
		for(int i=1;i<=N;i++){
			scanf("%d",&info[i]);
			adde(i,i+N,info[i]);
			for(int j=0;j<P;j++){
				scanf("%d",&input[i][j]);
			}
			for(int j=0;j<P;j++){
				scanf("%d",&output[i][j]);
			}	
		}
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				if(i==j){
					if(checkInputZero(i)) adde(s,i,info[i]);
					if(checkOutputOne(i)) adde(i+N,t,info[i]);
				}else{
					if(check(i,j)) adde(i+N,j,info[i]),vis[i+N][j]=1;
				}
			}
		}
		 */
		for(int i=1;i<=N;i++){
			scanf("%d",&info[i]);
			for(int j=1;j<=P;j++)
				scanf("%d",&input[i][j]);
			for(int j=1;j<=P;j++)
				scanf("%d",&output[i][j]);
		}
		init();
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++){
			if(i==j) continue;
			bool flag=true;
			for(int k=1;k<=P;k++)
				if(!check1(output[i][k],input[j][k])){
				flag=false;
				break;
			}
			if(flag){
				adde(i+N,j,info[i]);
				vis[i+N][j]=1;
			}
		}
		for(int i=1;i<=N;i++){
			adde(i,i+N,info[i]);//²ðµã
			if(ck1(i)) adde(0,i,info[i]);
			if(ck2(i)) adde(i+N,2*N+1,info[i]);
		}
		int ans=isap(0,2*N+1,2*N+2);
		int cnt=0;
		for(int i=1;i<=N;i++){
			for(int j=head[i+N];j!=-1;j=edge[j].nxt){
				int v=edge[j].to;
				if(vis[i+N][v]&&edge[j].flow>0) cnt++;
			}
		}
		printf("%d %d\n",ans,cnt);
		for(int i=1;i<=N;i++){
			for(int j=head[i+N];j!=-1;j=edge[j].nxt){
				int v=edge[j].to;
				if(vis[i+N][v]&&edge[j].flow>0) printf("%d %d %d\n",i,v,edge[j].flow);
			}
		}
	}	
	return 0;
}
