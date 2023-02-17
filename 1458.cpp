#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

const int max_n=5010;
char a[max_n],b[max_n];
int dp[max_n][max_n];
int main(){
	while(scanf("%s %s",a,b)!=EOF){
		int l1=strlen(a);
		int l2=strlen(b);
		for(int i=0;i<=l2;i++) dp[0][i]=0;
		for(int i=0;i<=l1;i++) dp[i][0]=0;
		for(int i=1;i<=l1;i++){
			for(int j=1;j<=l2;j++){
				if(a[i-1]==b[j-1]) dp[i][j]=dp[i-1][j-1]+1;
				else{
					dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
				}
			}
		}
		printf("%d\n",dp[l1][l2]);
	}
	return 0;
}
