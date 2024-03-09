#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=55;
int graph[max_n][max_n];
int degree[max_n];
int N;
void dfs(int u){
	for(int v=1;v<=50;v++){
		if(graph[u][v]){
			graph[u][v]--;
			graph[v][u]--;
			dfs(v);
			printf("%d %d\n",v,u);
		}
	}
}
int main(){
	int T;
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++){
		scanf("%d",&N);
		memset(graph,0,sizeof(graph));
		memset(degree,0,sizeof(degree));
		int x,y;
		int color;
		while(N--){
			scanf("%d %d",&x,&y);
			color=x;
			graph[x][y]++;
			graph[y][x]++;
			degree[x]++;
			degree[y]++;
		}
		if(kase!=1)	printf("\n");
		printf("Case #%d\n",kase);
		bool ok=true;
		for(int i=1;i<=50;i++){
			if(degree[i]%2!=0){
				printf("some beads may be lost\n");
				ok=false;
				break;
			}
		} 
		if(ok){
			dfs(color);
		}
	}
	return 0;
}
