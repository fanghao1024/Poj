#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const int max_n=1005;
const int max_e=100005;
int head1[max_n],head2[max_n];
struct Edge{
	int to,w;
	int nxt;
}edge1[max_e],edge2[max_e];
int cnt1,cnt2;
int N,M,S,T,K;
int Tdis[max_n];
bool Tvis[max_n];
typedef pair<int,int> P;
int k;

void add_edge1(int x,int y,int w){
	edge1[cnt1].to=y;
	edge1[cnt1].w=w;
	edge1[cnt1].nxt=head1[x];
	head1[x]=cnt1++;
}
void add_edge2(int x,int y,int w){
	edge2[cnt2].to=y;
	edge2[cnt2].w=w;
	edge2[cnt2].nxt=head2[x];
	head2[x]=cnt2++;
}
void dij(int t){
	memset(Tdis,0x3f,sizeof(Tdis));
	memset(Tvis,0,sizeof(Tvis));
	Tdis[t]=0;
	priority_queue<P,vector<P>,greater<P> > pqp;
	pqp.push(make_pair(0,t));

	while(!pqp.empty()){
		P p=pqp.top();
		pqp.pop();
		if(Tvis[p.second]) continue;
		Tvis[p.second]=1;
		for(int i=head2[p.second];i!=-1;i=edge2[i].nxt){
			int v=edge2[i].to;
			if(!Tvis[v]&&Tdis[v]>p.first+edge2[i].w){
				Tdis[v]=p.first+edge2[i].w;
				pqp.push(make_pair(Tdis[v],v));
			}
		}
	}
}
struct Node{
	int v;//当前结点编号
	int dis;//从源点到该结点的距离
	int pre;//从该结点到终点的最短距离
	Node(){};
	Node(int _v,int _dis,int _pre){
		v=_v;
		dis=_dis;
		pre=_pre;
	}
	bool operator<(const Node& a) const{
		return dis+pre>a.dis+a.pre;
	}
};
int nums[max_n];
int astar(){
	memset(nums,0,sizeof(nums));
	priority_queue<Node> pqn;
	pqn.push(Node(S,0,0));
	
	while(!pqn.empty()){
		Node node=pqn.top();
		pqn.pop();
		nums[node.v]++;
		if(node.v==T&&nums[node.v]==K){
			return node.dis+node.pre;
		}
		if(nums[node.v]>K) continue;
		for(int i=head1[node.v];i!=-1;i=edge1[i].nxt){
			pqn.push(Node(edge1[i].to,node.dis+edge1[i].w,Tdis[edge1[i].to]));
		}
	}
	return -1;
}
int main(){
	scanf("%d %d",&N,&M);
	memset(head1,-1,sizeof(head1));
	memset(head2,-1,sizeof(head2));
	cnt1=cnt2=0;
	int x,y,w;
	for(int i=0;i<M;i++){
		scanf("%d %d %d",&x,&y,&w);
		add_edge1(x,y,w);
		add_edge2(y,x,w);
	}
	scanf("%d %d %d",&S,&T,&K);
	dij(T);
	k=0;
	if(S==T) K++;
	if(!Tvis[S]){
		printf("-1\n");
	}else{
		printf("%d\n",astar());
	}
	return 0;
}
