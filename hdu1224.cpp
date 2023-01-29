#include<stdio.h>
#include<string.h>
#include<stack>
#include<algorithm>
using namespace std;
int N,M;
const int max_n=105;
int fun[max_n];
bool path[max_n][max_n];
int pre[max_n];
int sum[max_n];
int degree[max_n];
bool vis[max_n];
void TopoSort(){
	memset(sum,0,sizeof(sum));
	memset(vis,0,sizeof(vis));
	pre[1]=-1;
	vis[1]=1;
	for(int i=2;i<=N+1;i++){
		if(path[1][i]){
			if(sum[i]<sum[1]+fun[i]){
				sum[i]=sum[1]+fun[i];
				pre[i]=1;
				--degree[i];
			}
		}
	}
	for(int j=1;j<=N;j++){
		for(int i=2;i<=N+1;i++){
			if(!vis[i]&&!degree[i]){
				vis[i]=1;
				for(int k=1;k<=N+1;k++){
					if(path[i][k]){
						if(sum[k]<sum[i]+fun[k]){
							sum[k]=sum[i]+fun[k];
							pre[k]=i;
							--degree[k];
						}
					}
					
				}
				
			}
		}
	}
}
int main(){
	int case_nums;
	scanf("%d",&case_nums);
	for(int case_num=1;case_num<=case_nums;case_num++){
		scanf("%d",&N);
		for(int i=1;i<=N;i++){
			scanf("%d",&fun[i]);
		}
		fun[N+1]=0;
		scanf("%d",&M);
		int x,y;
		memset(path,0,sizeof(path));
		memset(degree,0,sizeof(degree));
		for(int i=0;i<M;i++){
			scanf("%d %d",&x,&y);
			path[x][y]=1;
			degree[y]++;
		}
		TopoSort();
		if(case_num-1) printf("\n");
		printf("CASE %d#\n",case_num);
		printf("points : %d\n",sum[N+1]);
		printf("circuit : ");
		int u=pre[N+1];
		degree[N]=1;
		int i=1;
		while(u!=-1){
			degree[N-i]=u;
			i++;
			u=pre[u];
		}
		int cnt=0;
		for(int j=N-i+1;j<=N;j++){
			if(cnt++) printf("->");
			printf("%d",degree[j]);
		}
		printf("\n");
	}
	return 0;
}
