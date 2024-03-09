#include<cstdio>
#include<cstring>

const int max_n=1e5+100;
int record[12],cnt[12],match[12][max_n];
bool g[12][max_n],vis[12];
int N,M;
bool maxmatch(int u){
	for(int i=0;i<M;i++){
		if(!vis[i]&&g[i][u]){
			vis[i]=true;
			if(cnt[i]<record[i]){
				match[i][cnt[i]++]=u;
				return true;
			}
			for(int j=0;j<cnt[i];j++){
				if(maxmatch(match[i][j])){
					match[i][j]=u;
					return true;
				}
			}
		}
		
	}
	return false;
}
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++) scanf("%d",&g[j][i]);
		}
		for(int i=0;i<M;i++) scanf("%d",&record[i]);
		memset(cnt,0,sizeof(cnt));
		bool flag=true;
		for(int i=0;i<N;i++){
			memset(vis,0,sizeof(vis));
			if(!maxmatch(i)){
				flag=false;
				break;
			}
		}
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
