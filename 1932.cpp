#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;

int N;
const int max_n=105;
bool path[max_n][max_n];
bool reach[max_n][max_n];
int energy[max_n];
int dis[max_n];
bool vis[max_n];
int power[max_n];
int cnt[max_n];
queue<int> q;
void floyd(){
	for(int k=1;k<=N;k++){
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				if(reach[i][j]||(reach[i][k]&&reach[k][j])) reach[i][j]=1;
			}
		}
	}
}
bool spfa(int u){
	memset(vis,0,sizeof(vis));
	memset(power,0,sizeof(power));
	memset(cnt,0,sizeof(cnt));
	
	vis[u]=1;
	power[u]=100;
	cnt[u]++;
	while(!q.empty()) q.pop();
	q.push(u);
	while(!q.empty()){
		int v=q.front();
		q.pop();
		vis[v]=0;
		for(int i=1;i<=N;i++){
			if(path[v][i]&&power[i]<power[v]+energy[i]&&power[v]+energy[i]>0){
				power[i]=power[v]+energy[i];
				if(!vis[i]){
					if(++cnt[i]>=N){
						return reach[v][N];
					}
					q.push(i);
					vis[i]=1;
				}
			}
		}
	}
	return power[N]>0;
}
int main(){
	while(scanf("%d",&N)&&N!=-1){
		int k,x;
		memset(path,0,sizeof(path));
		memset(reach,0,sizeof(reach));
		for(int i=1;i<=N;i++){
			scanf("%d %d",&energy[i],&k);
			for(int j=0;j<k;j++){
				scanf("%d",&x);
				path[i][x]=1;
				reach[i][x]=1;
			}
		}
		floyd();
		
		if(!reach[1][N]){
			printf("hopeless\n");
			continue;
		}
		if(spfa(1)){
			printf("winnable\n");
		}else{
			printf("hopeless\n");
		}
	}
	return 0;
}
