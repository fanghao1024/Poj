#include<iostream>
#include<string.h>
#include<queue>
using namespace std;

const int max_m=400005;
const int max_n=100005;

int N,M;
int head[max_n];
int dis[max_n];
const int inf=0x7fffffff;
struct Edge{
	int to,color;
	int nxt;
}edge[max_m];
int cnt;
bool vis[max_n];
void add_edge(int x,int y,int c){
	edge[cnt].to=y;
	edge[cnt].color=c;
	edge[cnt].nxt=head[x];
	head[x]=cnt;
	cnt++;
}
queue<int> q1,q2,q3;
void bfs1(){
	memset(vis,0,sizeof(vis));
	dis[N]=0;
	vis[N]=1;
	while(!q1.empty()) q1.pop();
	q1.push(N);
	while(!q1.empty()){
		int u=q1.front();
		q1.pop();
		vis[u]=true; //add
		for(int i=head[u];i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(vis[v]) continue;
			vis[v]=true;
			dis[v]=dis[u]+1;
			q1.push(v);
		}
	}
}
void bfs2(){
	while(!q1.empty()) q1.pop();
	while(!q2.empty()) q2.pop();
	while(!q3.empty()) q3.pop();
	memset(vis,0,sizeof(vis));
	vis[1]=1;
	for(int i=head[1];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(dis[v]==dis[1]-1){
			q1.push(v);
			q2.push(edge[i].color);
			//vis[v]=true;
		}
	}
	bool first=true;
	while(!q1.empty()){
		int minc=inf;
		while(!q1.empty()){
			int u=q1.front();
			int c=q2.front();
			q1.pop();
			q2.pop();
			if(minc>c){
				minc=c;
				while(!q3.empty()){
					q3.pop();
				}
			}
			if(minc==c){
				q3.push(u);
			}
		}
		if(first){
			first=false;
		}else{
			cout<<" ";
		}
		cout<<minc;
		while(!q3.empty()){
			int u=q3.front();
			q3.pop();
			if(vis[u]) //add
				continue;//add
			vis[u]=true;//add
			for(int i=head[u];i!=-1;i=edge[i].nxt){
				int v=edge[i].to;
				int c=edge[i].color;
				//if(vis[v]) continue;
				//vis[v]=true;
				if(dis[v]==dis[u]-1){
					q1.push(v);
					q2.push(c);
				}
				
			}
		}
		
	}
}
int main(){
	//while(scanf("%d %d",&N,&M)!=EOF){
	while(cin>>N>>M){
		int x,y,c;
		cnt=0;
		memset(head,-1,sizeof(head));
		for(int i=0;i<M;i++){
			cin>>x>>y>>c;
			add_edge(x,y,c);
			add_edge(y,x,c);
		}
		bfs1();
		cout<<dis[1]<<endl;
		bfs2();
		cout<<endl;
	}
	return 0;
}

