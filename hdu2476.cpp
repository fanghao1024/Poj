#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=105;
const int inf=0x3f3f3f3f;

char s1[max_n],s2[max_n];
int dp[max_n][max_n];
int main(){
	while(scanf("%s %s",s1+1,s2+1)!=EOF){
		int len=strlen(s1+1);
		//memset(dp,inf,sizeof(dp));
		for(int i=1;i<=len;i++) dp[i][i]=1;
		for(int l=2;l<=len;l++){
			for(int i=1;i+l-1<=len;i++){
				int r=i+l-1;
				dp[i][r]=inf;
				if(s2[i]==s2[r]) dp[i][r]=dp[i+1][r];
				else{
					for(int k=i;k<r;k++){
						dp[i][r]=min(dp[i][r],dp[i][k]+dp[k+1][r]);
					}
				}
			}
		}
		for(int i=1;i<=len;i++){
			if(s1[i]==s2[i]) dp[1][i]=dp[1][i-1];
			else{
				for(int k=1;k<i;k++){
					dp[1][i]=min(dp[1][i],dp[1][k]+dp[k+1][i]);
				}
			}
		}
		printf("%d\n",dp[1][len]);
	}
	return 0;
}
