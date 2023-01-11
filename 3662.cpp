#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

int N,P,K;
typedef pair<int,int> PP;
const int max_n=1005;
struct Edge{
	int to,cost;
};
vector<Edge> edge[max_n];
bool visited[max_n];
bool bfs(int s,int mid,int k){
	if(s==N) return true;
	for(int i=1;i<=N;i++) visited[i]=true;
	queue<PP> q;
	q.push(make_pair(s,k));
	visited[s]=false;
	while(!q.empty()){
		PP p=q.front();
		q.pop();
		int v=p.first;
		int vk=p.second;
		for(int i=0;i<edge[v].size();i++){
			if(visited[edge[v][i].to]){
				if(edge[v][i].cost<=mid){
					if(edge[v][i].to==N) return true;
					q.push(make_pair(edge[v][i].to,vk));
					visited[edge[v][i].to]=false;
				}else{
					if(vk>0){
						if(edge[v][i].to==N) return true;
						q.push(make_pair(edge[v][i].to,vk-1));
						visited[edge[v][i].to]=false;
					}
				}
			}
		}
	}
	return false;
}
bool check(int mid){
	for(int i=1;i<=N;i++){
		visited[i]=true;
	}
	if(bfs(1,mid,K)){
		return true;
	}else{
		return false;
	}
}
int main(){
	scanf("%d %d %d",&N,&P,&K);
	int Ai,Bi,Li;
	Edge e;
	for(int i=0;i<P;i++){
		scanf("%d %d %d",&Ai,&Bi,&Li);
		e.to=Bi;
		e.cost=Li;
		edge[Ai].push_back(e);
		e.to=Ai;
		edge[Bi].push_back(e);
	}
	int ub=1000000;
	int lb=1;
	while(ub>lb+1){
		int mid=(ub+lb)/2;
		if(check(mid)){
			ub=mid;
		}else{
			lb=mid;
		}
	}
	printf("%d\n",ub);
	return 0;
}
