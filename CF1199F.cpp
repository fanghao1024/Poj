#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int max_n=55;

char ch[max_n][max_n];
int N;
int dp[max_n][max_n][max_n][max_n];

int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%s",ch[i]+1);
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			if(ch[i][j]=='#') dp[i][j][i][j]=1;
			else dp[i][j][i][j]=0;
		}
	}
	for(int lenx=1;lenx<=N;lenx++){
		for(int leny=1;leny<=N;leny++){
			for(int x1=1;x1+lenx-1<=N;x1++){
				for(int y1=1;y1+leny-1<=N;y1++){
					int x2=x1+lenx-1,y2=y1+leny-1;
					if(x1==x2&&y1==y2) continue;
					dp[x1][y1][x2][y2]=max(abs(x2-x1),abs(y2-y1))+1;
					for(int k=x1;k<x2;k++){
						dp[x1][y1][x2][y2]=min(dp[x1][y1][x2][y2],dp[x1][y1][k][y2]+dp[k+1][y1][x2][y2]);
					}
					for(int k=y1;k<y2;k++){
						dp[x1][y1][x2][y2]=min(dp[x1][y1][x2][y2],dp[x1][y1][x2][k]+dp[x1][k+1][x2][y2]);
					}
				}
			}
		}
	}
	printf("%d\n",dp[1][1][N][N]);
	return 0;
}
