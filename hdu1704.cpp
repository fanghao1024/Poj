#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
using namespace std;

const int max_n=505;
bitset<max_n> d[max_n];
int N,M;
void floyd(){
	for(int k=1;k<=N;k++){
		for(int i=1;i<=N;i++){
			if(d[i][k]) d[i]|=d[k];
		}
	}
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&N,&M);
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++) d[i][j]=(i==j);
		}
		int x,y;
		while(M--){
			scanf("%d %d",&x,&y);
			d[x][y]=1;
		}
		floyd();
		int tot=0;
		for(int i=1;i<=N;i++){
			for(int j=i+1;j<=N;j++){
				if(d[i][j]==0&&d[j][i]==0) tot++;
			}
		}
		printf("%d\n",tot);
	}
	return 0;
}
