#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int max_n=5e3+10;
int dis[max_n],head[max_n],cnt,N,M,inq[max_n],Neg[max_n];
struct Edge{
	int to,w;
	int nxt;
}edge[max_n<<1];
void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
	memset(dis,0x3f,sizeof(dis));
	memset(inq,0,sizeof(inq));
	memset(Neg,0,sizeof(Neg));
}
void add_edge(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=w;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
bool spfa(){
	queue<int> q;
	q.push(0);
	inq[0]=0;
	dis[0]=0;
	Neg[0]=1;int a=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		inq[u]=0;
		for(int j=head[u];j!=-1;j=edge[j].nxt){
			int v=edge[j].to,w=edge[j].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!inq[v]){
					q.push(v);
					inq[v]=1;
					Neg[v]++;
					if(Neg[v]>N) return false;
				}
			}
		}
	}
	return true;
}
int main(){
	scanf("%d %d",&N,&M);
	init();
	for(int i=1;i<=N;i++) add_edge(0,i,0);
	int x,y,w;
	while(M--){
		scanf("%d %d %d",&x,&y,&w);
		add_edge(y,x,w);
	}
	
	if(spfa()){
		for(int i=1;i<=N;i++){
			if(i-1) printf(" ");
			printf("%d",dis[i]);
		}
	}else{
		printf("NO\n");
	}
	return 0;
}
