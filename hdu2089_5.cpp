#include<cstdio>
#include<cstring>

int dp[15][10];
int dig[15];
int N,M;
void init(){
	dp[0][0]=1;
	for(int i=1;i<=9;i++){
		for(int j=0;j<=9;j++){
			if(j==4) dp[i][j]=0;
			else{
				for(int k=0;k<=9;k++){
					if(j==6&&k==2) continue;
					else dp[i][j]+=dp[i-1][k];
				}
			}
		}
	}
}
int solve(int m){
	int pos=0;
	while(m){
		dig[++pos]=m%10;
		m/=10;
	}
	int ans=0;
	dig[pos+1]=0;
	for(int i=pos;i>=1;i--){
		for(int j=0;j<dig[i];j++){
			if(j==2&&dig[i+1]==6) continue;
			else ans+=dp[i][j];
		}
		if(dig[i]==4||(dig[i]==2&&dig[i+1]==6)){
			ans--;
			break;
		}
	}
	return ans;
}
int main(){
	memset(dp,0,sizeof(dp));
	init();
	while(scanf("%d%d",&N,&M)&&(N+M)){
		printf("%d\n",solve(M)-solve(N-1));
	}
	return 0;
}
