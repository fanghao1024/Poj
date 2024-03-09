#include<cstdio>
#include<cstring>
#include<algorithm>
#include<deque>
#include<map>
using namespace std;

typedef pair<int,int> P;
const int max_n=110;
const int max_m=1e4+10;
int head[max_n],cnt,dis[max_n],N,M,inq[max_n],S;
struct Edge{
	int to,w;
	int nxt;
}edge[max_m<<1];
void init(){
	memset(head,-1,sizeof(head));
	memset(dis,0x3f,sizeof(dis));
	memset(inq,0,sizeof(inq));
	cnt=0;
}
void add_edge(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=w;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void spfa(){
	deque<int> q;
	q.push_back(S);
	inq[S]=1;
	dis[S]=0;
	while(!q.empty()){
		int u=q.front();q.pop_front();
		inq[u]=0;
		for(int i=head[u];i!=-1;i=edge[i].nxt){
			int v=edge[i].to,w=edge[i].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!inq[v]){
					if(dis[v]<dis[q.front()]) q.push_front(v);
					else q.push_back(v);
					inq[v]=1;
				}
			}
		}
	}
}
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		if(!N&&!M) break;
		init();
		int x,y,w;
		while(M--){
			scanf("%d %d %d",&x,&y,&w);
			add_edge(x,y,w);
			add_edge(y,x,w);
		}
		S=1;
		spfa();
		printf("%d\n",dis[N]);
	}
	return 0;
}
