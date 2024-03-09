#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=8e4+10;

int n,opt,mod,mi,ma;
ll dp[max_n];
ll ans[max_n];
char ch[20];
int main(){
	scanf("%d %d %d %d %d",&n,&opt,&mod,&mi,&ma);
	ll l,r,x,res;
	while(opt--){
		scanf("%s",ch);
		if(ch[0]=='A'){
			scanf("%lld %lld %lld",&l,&r,&x);
			dp[l]+=x;
			dp[r+1]-=x;
		}else{
			scanf("%lld %lld",&l,&r);
			res=0;
			for(int i=1;i<=r;i++){
				ans[i]=ans[i-1]+dp[i];
				if(i>=l){
					int temp=(ans[i]*i)%mod;
					if(temp>=mi&&temp<=ma) res++;
				}
			}
			printf("%lld\n",res);
		}
	}
	for(int i=1;i<=n;i++) ans[i]=dp[i];
	for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
	for(int i=1;i<=n;i++) ans[i]=ans[i]*i%mod,ans[i]=(ans[i]>=mi&&ans[i]<=ma)?1:0,ans[i]+=ans[i-1];
	int f;
	scanf("%d",&f);
	while(f--){
		scanf("%lld %lld",&l,&r);
		printf("%lld\n",ans[r]-ans[l-1]);
	}
	return 0;
}
