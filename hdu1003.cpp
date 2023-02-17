#include<cstdio>

const int max_n=100010;
int T,N;
int num[max_n];
int dp[max_n],s[max_n];

int main(){
	scanf("%d",&T);
	for(int caseNo=1;caseNo<=T;caseNo++){
		scanf("%d",&N);
		for(int i=0;i<N;i++){
			scanf("%d",&num[i]);
		}
		dp[0]=num[0];
		s[0]=0;
		for(int i=1;i<N;i++){
			if(dp[i-1]>=0){
				dp[i]=num[i]+dp[i-1];
				s[i]=s[i-1];
			}else{
				dp[i]=num[i];
				s[i]=i;
			}
			
		} 
		int ans=dp[0];
		int pos=0;
		for(int i=1;i<N;i++){
			if(ans<dp[i]){
				ans=dp[i];
				pos=i;
			}
		}
		if(caseNo-1) printf("\n");
		printf("Case %d:\n",caseNo);
		printf("%d %d %d\n",ans,s[pos]+1,pos+1);
	}
	return 0;
}
