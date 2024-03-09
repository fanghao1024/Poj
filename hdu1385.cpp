#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=510;
const int inf=0x3f3f3f3f;

int tax[max_n],path[max_n][max_n],cost[max_n][max_n];
int N;
void floyd(){
	for(int k=1;k<=N;k++){
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				int len=cost[i][k]+cost[k][j]+tax[k];
				if(cost[i][j]>len){
					cost[i][j]=len;
					path[i][j]=path[i][k];
				}
				else if(cost[i][j]==len&&path[i][j]>path[i][k]){
					path[i][j]=path[i][k];
				}
			}
		}
	}
}
int main(){
	while(scanf("%d",&N)&&N){
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				scanf("%d",&cost[i][j]);
				if(cost[i][j]==-1) cost[i][j]=inf;
				path[i][j]=j;
			}
		}
		for(int i=1;i<=N;i++) scanf("%d",&tax[i]);
		//memset(path,-1,sizeof(path));
		floyd();
		int g,h;
		while(scanf("%d %d",&g,&h)!=EOF){
			if(g==-1&&h==-1) break;
			printf("From %d to %d :\n",g,h);
			printf("Path: %d",g);
			int x=g;
			while(x!=h){
				printf("-->%d",path[x][h]);
				x=path[x][h];
			}
			printf("\n",h);
			printf("Total cost : %d\n\n",cost[g][h]);
		}
		
	}
	return 0;
}
