#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
int T,cnt;
ll P;
int prime[2000007];
bool vis[10000007];
void init(){
	memset(vis,0,sizeof(vis));
	cnt=0;
	for(int i=2;i<=10000000;i++){
		if(!vis[i]) prime[cnt++]=i;
		for(int j=0;j<cnt;j++){
			if((ll)i*prime[j]>1e7) break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
}

bool check(ll x){
	if(x<2) return false;
	if(x==2) return true;
	if(x%2==0) return false;
	int num=sqrt(x);
	for(int i=0;i<cnt&&prime[i]<=num;i++){
		if(x%prime[i]==0) return false;
	}
	return true;
}
//(a*b) mod m
ll mulM(ll a,ll b,ll m){
	ll res=0;
	while(b){
		if(b&1){
			res=(res+a)%m;
		}
		a=(a+a)%m;
		b>>=1;
	}
	return res;
}
//a^u mod n
ll fast_pow(ll a,ll u,ll n){
	ll res=1;
	while(u){
		if(u&1) res=mulM(res,a,n);
		a=mulM(a,a,n);
		u>>=1;
	}
	return res;
}
int main(){
	init();
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&P);
		ll ans=P-1;
		for(ll i=P-1;i;i--){
			if(check(i)) break;
			ans=mulM(ans,fast_pow(i,P-2,P),P)%P;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
