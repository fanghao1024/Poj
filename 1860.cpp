#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;

const int max_n=105;
int N,M,S;
double V;
int head[max_n];
int cnt;
double dis[max_n];
bool inq[max_n];
int sum[max_n];
struct Edge{
	int to;
	double rate,com;
	int nxt;
}edge[805];

void add_edge(int x,int y,double r,double c){
	edge[++cnt].to=y;
	edge[cnt].rate=r;
	edge[cnt].com=c;
	edge[cnt].nxt=head[x];
	head[x]=cnt;
}
bool spfa(int u){
	memset(dis,0,sizeof(dis));
	memset(inq,0,sizeof(inq));
	memset(sum,0,sizeof(sum));
	dis[u]=V;
	queue<int> q;
	q.push(u);
	inq[u]=1;
	sum[u]++;
	while(!q.empty()){
		int p=q.front();
		q.pop();
		inq[p]=0;
		if(p==S&&dis[p]>V) return true;
		for(int i=head[p];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(dis[v]<(dis[p]-edge[i].com)*edge[i].rate){
				dis[v]=(dis[p]-edge[i].com)*edge[i].rate;
				if(!inq[v]){
					q.push(v);
					if(++sum[v]>=N) return true;
					inq[v]=1;
				}
			}
		}
	}
	return false;
}
int main(){
	scanf("%d %d %d %lf",&N,&M,&S,&V);
	int x,y;
	double r1,c1,r2,c2;
	cnt=0;
	memset(head,0,sizeof(head));
	
	for(int i=0;i<M;i++){
		scanf("%d %d %lf %lf %lf %lf",&x,&y,&r1,&c1,&r2,&c2);
		add_edge(x,y,r1,c1);
		add_edge(y,x,r2,c2);
	}
	
	if(spfa(S)){
		printf("YES\n");
	}else{
		printf("NO\n");
	}
	
	return 0;
}
