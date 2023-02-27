#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=1e5+10;

int num[max_n];
ll sum[max_n];
int st[max_n];
ll dp[max_n];
int N;
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%d",&num[i]);
	for(int i=1;i<=N;i++) sum[i]=num[i]+sum[i-1];
	int f=-1;
	for(int i=1;i<=N;i++){
		if(f<0||num[i]>=num[st[f]]){
			st[++f]=i;
		}
		else{
			while(f>=0&&num[i]<num[st[f]]){
				int now=st[f--];
				if(f==-1){
					dp[now]=sum[i-1]*num[now];
				}else{
					dp[now]=(sum[i-1]-sum[st[f]])*num[now];
				}
			}
			st[++f]=i;
		}
	}
	while(f>=0){
		int now=st[f--];
		if(f==-1){
			dp[now]=sum[N]*num[now];
		}else{
			dp[now]=(sum[N]-sum[st[f]])*num[now];
		}
	}
	ll ans=0;
	for(int i=1;i<=N;i++) ans=max(ans,dp[i]);
	printf("%lld\n",ans);
	return 0;
}
