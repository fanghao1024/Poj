#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;

const int max_n=105;
int N,M,S;
double V;
int cnt;
double dis[max_n];
bool inq[max_n];
int sum[max_n];
struct Edge{
	int a,b;
	double rate,com;
}edge[210];

void add_edge(int x,int y,double r,double c){
	edge[cnt].a=x;
	edge[cnt].b=y;
	edge[cnt].rate=r;
	edge[cnt].com=c;
	cnt++;
}
bool bellman_ford(int u){
	memset(dis,0,sizeof(dis));
	dis[u]=V;
	bool flag;
	for(int i=1;i<N;i++){
		flag=false;
		for(int j=0;j<cnt;j++){
			if(dis[edge[j].b]<(dis[edge[j].a]-edge[j].com)*edge[j].rate){
				dis[edge[j].b]=(dis[edge[j].a]-edge[j].com)*edge[j].rate;
				flag=true;
			}
		}
		if(!flag) return false;
	}
	for(int j=0;j<cnt;j++){
		if(dis[edge[j].b]<(dis[edge[j].a]-edge[j].com)*edge[j].rate){
			return true;
		}
	}
	return false;
}
int main(){
	scanf("%d %d %d %lf",&N,&M,&S,&V);
	int x,y;
	double r1,c1,r2,c2;
	cnt=0;
	
	for(int i=0;i<M;i++){
		scanf("%d %d %lf %lf %lf %lf",&x,&y,&r1,&c1,&r2,&c2);
		add_edge(x,y,r1,c1);
		add_edge(y,x,r2,c2);
	}
	
	if(bellman_ford(S)){
		printf("YES\n");
	}else{
		printf("NO\n");
	}
	
	return 0;
}
