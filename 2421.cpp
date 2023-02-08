#include<stdio.h>
#include<string.h>

const int max_n=103;
int dis[max_n][max_n];
int N,Q;
int rec[max_n];
bool vis[max_n];
int prim(int u){
	memset(vis,0,sizeof(vis));
	memset(rec,0x3f,sizeof(rec));
	vis[u]=1;
	rec[u]=0;
	int ans=0;
	for(int i=1;i<N;i++){
		int d=0x3fffffff;
		int t=1;
		for(int j=2;j<=N;j++){
			if(!vis[j]){
				if(rec[j]>dis[u][j]){
					rec[j]=dis[u][j];
				}
				if(d>rec[j]){
					d=rec[j];
					t=j;
				}
			}
		}
		if(t==1) return -1;
		vis[t]=1;
		ans+=rec[t];
		u=t;
	}
	return ans;
}
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			scanf("%d",&dis[i][j]);
		}
	}
	scanf("%d",&Q);
	int x,y;
	for(int i=0;i<Q;i++){
		scanf("%d %d",&x,&y);
		dis[x][y]=dis[y][x]=0;
	}
	int ans=prim(1);
	if(ans!=-1){
		printf("%d\n",ans);
	}
	return 0;
}
