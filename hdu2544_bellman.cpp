#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=110;
const int max_m=1e4+10;

struct Edge{
	int from,to;
	int w;
}edge[max_m<<1];
int N,M,dis[max_n],cnt,S;
void bellman_ford(){
	memset(dis,0x3f,sizeof(dis));
	dis[S]=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<cnt;j++){
			int x=edge[j].from,y=edge[j].to,w=edge[j].w;
			if(dis[y]>dis[x]+w) dis[y]=dis[x]+w;
		}
	}
}
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		if(!N&&!M) break;
		cnt=0;
		int x,y,w;
		while(M--){
			scanf("%d %d %d",&x,&y,&w);
			edge[cnt].from=x;edge[cnt].to=y;edge[cnt].w=w;
			cnt++;
			edge[cnt].from=y;edge[cnt].to=x;edge[cnt].w=w;
			cnt++;
		}
		S=1;
		bellman_ford();
		printf("%d\n",dis[N]);
	}
	return 0;
}
