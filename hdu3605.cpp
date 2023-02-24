#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e5+100;

int N,M;
bool vis[15];
bool g[15][max_n];
int match[15][max_n];
int record[15],cnt[15];

bool maxmatch(int u){
	for(int i=0;i<M;i++){
		if(g[i][u]&&!vis[i]){
			vis[i]=true;
			if(cnt[i]<record[i]){
				match[i][cnt[i]++]=u;
				return true;
			}else{
				for(int j=0;j<cnt[i];j++){
					if(maxmatch(match[i][j])){
						match[i][j]=u;
						return true;
					}
				}
			}
		}
	}
	return false;
}
void init(){
	memset(cnt,0,sizeof(cnt));
}
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		init();
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				scanf("%d",&g[j][i]);
			}
		}
		for(int i=0;i<M;i++) scanf("%d",&record[i]);
		
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
