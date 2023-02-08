#include<cstdio>
#include<cstring>

const int max_n=105;
const int max_e=5010;
bool path[max_n][max_n];
int N,K,M;

int ans;
int rec[max_n];
bool ok(int u,int color){
	for(int i=1;i<u;i++){
		if(path[i][u]&&rec[i]==color) return false;
	}
	return true;
}
void dfs(int u){
	if(u>N){
		ans++;
		return;
	}
	for(int i=0;i<M;i++){
		if(ok(u,i)){
			rec[u]=i;
			dfs(u+1);
		}
	}
}
int main()
{
	scanf("%d %d %d",&N,&K,&M);
	memset(path,0,sizeof(path));
	int x,y;
	for(int i=0;i<K;i++){
		scanf("%d %d",&x,&y);
		path[x][y]=path[y][x]=1;
	}
	ans=0;
	dfs(1);
	printf("%d\n",ans);
	return 0;
}
