#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char matrix[10][10];
int N,K,cnt,ans;

bool row[10],col[10];
void dfs(int k,int r){
	if(k==K){
		ans++;
		return ;
	}
	if(r>=N) return ;
	for(int i=0;i<N;i++){
		if(matrix[r][i]=='#'&&!col[i]){
			col[i]=1;
			dfs(k+1,r+1);
			col[i]=0;
		}
	}
	dfs(k,r+1);
}
int main(){
	while(scanf("%d %d",&N,&K)!=EOF){
		if(N==-1&&K==-1) break;
		cnt=0;
		for(int i=0;i<N;i++){
			scanf("%s",matrix[i]);
		}
		ans=0;
		memset(col,0,sizeof(col));
		dfs(0,0);
		printf("%d\n",ans);
	}
	return 0;
}
