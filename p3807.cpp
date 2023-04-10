#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=1e5+10;

ll factor[max_n];
ll n,m,p;
void init(){
	factor[0]=1;
	for(int i=1;i<=p;i++){
		factor[i]=(factor[i-1]*i)%p;
	}
}
ll fast_pow(ll a,ll n,ll m){
	ll res=1;
	a%=m;
	while(n){
		if(n&1) res=(res*a)%m;
		a=(a*a)%m;
		n>>=1;
	}
	return res;
}
ll inv(ll x,ll m){
	return fast_pow(factor[x],m-2,m);
}
ll C(ll n,ll r,ll mod){
	if(r>n) return 0;
	return (factor[n]*inv(r,mod))%mod*inv(n-r,mod)%mod;
}
ll Lucas(ll n,ll r,ll mod){
	if(r==0) return 1;
	return C(n%mod,r%mod,mod)*Lucas(n/mod,r/mod,mod)%mod;
}
int main(){
	int T;	
	scanf("%d",&T);
	while(T--){
		scanf("%lld %lld %lld",&n,&m,&p);
		init();
		printf("%lld\n",Lucas(n+m,m,p));
	}
	return 0;
}
