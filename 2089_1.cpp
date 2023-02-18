#include<cstdio>
#include<cstring>

int dp[15][15],num[15];
int N,M;
void init(){
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for(int i=1;i<=9;i++){
		for(int j=0;j<=9;j++){
			if(j==4) dp[i][j]=0;
			else{
				for(int k=0;k<=9;k++){
					if(j==6&&k==2) continue;
					dp[i][j]+=dp[i-1][k];
				}
			}
		}
	}
}
int solve(int m){
	int cnt=0;
	while(m){
		num[++cnt]=m%10;
		m/=10;
	}
	int ans=0;
	num[cnt+1]=0;
	for(int i=cnt;i>=1;i--){
		for(int j=0;j<num[i];j++){
			if(j==2&&num[i+1]==6) continue;
			else ans+=dp[i][j];
		}
		if(num[i]==4||num[i]==2&&num[i+1]==6){ans--;break;}
	}
	return ans;
}
int main(){
	init();
	while(scanf("%d %d",&N,&M)!=EOF){
		if(!N&&!M) break;
		printf("%d\n",solve(M)-solve(N-1));
	}
	return 0;
}
