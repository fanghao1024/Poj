#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

const int INF=1000000;
const int max_e=100010;
const int max_n=1010;
int d1[max_n];
int d2[max_n];
struct Edge{
	int to,T;
	Edge(int to,int T){
		this->to=to;
		this->T=T;
	}
};
vector<Edge> edge1[max_n],edge2[max_n];
int N,M,X;
typedef pair<int,int> P;

int main(){
	scanf("%d %d %d",&N,&M,&X);
	int a,b,t;
	for(int i=0;i<M;i++){
		scanf("%d %d %d",&a,&b,&t);
		edge1[a].push_back(Edge(b,t));
		edge2[b].push_back(Edge(a,t));
	}
	for(int i=1;i<=N;i++){
		d1[i]=INF;
		d2[i]=INF;
	}
	d1[X]=0;
	d2[X]=0;
	priority_queue<P,vector<P>,greater<P> >pq1;
	pq1.push(make_pair(0,X));
	int v,d;
	while(!pq1.empty()){
		P p=pq1.top();
		pq1.pop();
		v=p.second;
		d=p.first;
		if(d1[v]<d) continue;
		for(int i=0;i<edge1[v].size();i++){
			if(d1[edge1[v][i].to]>d1[v]+edge1[v][i].T){
				d1[edge1[v][i].to]=d1[v]+edge1[v][i].T;
				pq1.push(make_pair(d1[edge1[v][i].to],edge1[v][i].to));
			}
		}
	}
	priority_queue<P,vector<P>,greater<P> >pq2;
	pq2.push(make_pair(0,X));

	while(!pq2.empty()){
		P p=pq2.top();
		pq2.pop();
		v=p.second;
		d=p.first;
		if(d2[v]<d) continue;
		for(int i=0;i<edge2[v].size();i++){
			if(d2[edge2[v][i].to]>d2[v]+edge2[v][i].T){
				d2[edge2[v][i].to]=d2[v]+edge2[v][i].T;
				pq2.push(make_pair(d2[edge2[v][i].to],edge2[v][i].to));
			}
		}
	}
	int ans=-1;
	for(int i=1;i<=N;i++){
		//printf("%d %d %d\n",i,d1[i],d2[i]);
		ans=ans>d1[i]+d2[i]?ans:d1[i]+d2[i];
	}
	printf("%d\n",ans);
	return 0;
}
