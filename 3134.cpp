#include<stdio.h>
#include<queue>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int N;
bool vis[1005];
struct Node{
	int v;
	int pre;
	int dis;
	Node(){};
	Node(int v_,int pre_){
		v=v_;
		pre=pre_;
		//dis=abs(N-v_);
	}

};
int astar(){
	queue<Node> q;
	memset(vis,0,sizeof(vis));
	q.push(Node(1,0));
	vis[1]=1;
	while(!q.empty()){
		Node node=q.front();
		q.pop();
		
		if(node.v==N) return node.pre;

		if(node.v+1<=1000&&!vis[node.v+1]){
			q.push(Node(node.v+1,node.pre+1));
			vis[node.v+1]=1;
		}
		if(node.v*2<=1000&&!vis[node.v*2]){
			q.push(Node(node.v*2,node.pre+1));
			vis[node.v*2]=1;
		}
		if(node.v-1>0&&!vis[node.v-1]){
			q.push(Node(node.v-1,node.pre+1));
			vis[node.v-1]=1;
		}
		
	}
	return -1;
}
int main(){
	while(scanf("%d",&N)&&N){
		printf("%d\n",astar());
	}
	return 0;
}
