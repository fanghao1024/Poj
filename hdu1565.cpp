#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=23;
int num[max_n][max_n];
int N,top,ans;
int state[18000];
int dp[max_n][18000];
bool check(int x){
	if(x&(x<<1)) return 0;
	return 1;
}
void init(){
	top=0;
	for(int i=0;i<(1<<N);i++){
		if(check(i)){
			state[top++]=i;
		}
	}
}

int get_sum(int k,int i){
	int res=0;
	int pos=1;
	while(k){
		if(k&1) res+=num[i][pos];
		k>>=1;
		pos++;
	}
	return res;
}
void solve(){
	ans=0;
	memset(dp,0,sizeof(dp));
	for(int i=0;i<top;i++){
		int k=state[i];
		
		dp[1][i]=get_sum(k,1);
		ans=max(ans,dp[1][i]);
	}
	for(int i=2;i<=N;i++){
		for(int j=0;j<top;j++){
			int res=0;
			for(int k=0;k<top;k++){
				if(state[j]&state[k]) continue;
				res=max(res,dp[i-1][k]);
			}
			dp[i][j]=get_sum(state[j],i)+res;
			if(i==N) ans=max(ans,dp[i][j]);
		}
		
	}
}
int main(){
	while(scanf("%d",&N)!=EOF){
		init();
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				scanf("%d",&num[i][j]);
			}
		}
		solve();
		printf("%d\n",ans);
	}
	return 0;
}
