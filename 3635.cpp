#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int max_n=1005;
const int max_e=20005;

struct Edge{
	int to,w;
	int nxt;
}edge[max_e];
int p[max_n];
int head[max_n];
int N,M,cnt,Q;
int C,S,E;
bool vis[max_n][105];
int dp[max_n][105];
void add_edge(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=w;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}

struct Node{
	int curPos;//当前所在结点
	int curOil; //当前结点的当前油量
	int cost;//已消耗的油费
	Node(int _curPos,int _curOil,int _cost){
		this->curPos=_curPos;
		this->curOil=_curOil;
		this->cost=_cost;
	}
	bool operator<(const Node& a) const{
		return cost>a.cost;
	}
};

int bfs(){
	memset(vis,0,sizeof(vis));
	memset(dp,0x3f,sizeof(dp));
	priority_queue<Node> pqn;
	pqn.push(Node(S,0,0));
	vis[S][0]=1;
	dp[S][0]=0;
	while(!pqn.empty()){
		Node node=pqn.top();
		pqn.pop();
		vis[node.curPos][node.curOil]=1;
		if(node.curPos==E) return node.cost;
		if(node.curOil<C&&!vis[node.curPos][node.curOil+1]&&dp[node.curPos][node.curOil]+p[node.curPos]<dp[node.curPos][node.curOil+1]){
			dp[node.curPos][node.curOil+1]=dp[node.curPos][node.curOil]+p[node.curPos];
			pqn.push(Node(node.curPos,node.curOil+1,node.cost+p[node.curPos]));
		} 
		for(int i=head[node.curPos];i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			int w=edge[i].w;
			if(node.curOil>=w&&!vis[v][node.curOil-w]&&dp[v][node.curOil-w]>node.cost){
				dp[v][node.curOil-w]=node.cost;
				pqn.push(Node(v,node.curOil-w,node.cost));
				
			}
		}
	}
	return -1;
}
int main(){
		scanf("%d %d",&N,&M);
		for(int i=0;i<N;i++) scanf("%d",&p[i]);
		int x,y,w;
		memset(head,-1,sizeof(head));
		for(int i=0;i<M;i++){
			scanf("%d %d %d",&x,&y,&w);
			add_edge(x,y,w);
			add_edge(y,x,w);
		}
		scanf("%d",&Q);
		
		while(Q--){
			scanf("%d %d %d",&C,&S,&E);
			int ans=bfs();
			if(ans==-1){
				printf("impossible\n");
			}else{
				printf("%d\n",ans);
			}
		}
	return 0;
}
