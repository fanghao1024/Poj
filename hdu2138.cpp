#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
int N;
ll fast_pow(ll a,ll x,ll m){
	ll res=1;
	while(x){
		if(x&1) res=(res*a)%m;
		a=(a*a)%m;
		x>>=1;
	}
	return res;
}
bool witness(ll a,ll n){
	ll u=n-1,t=0;
	while(u&1==0){
		t++;
		u>>=1;
	}
	ll x1=fast_pow(a,u,n);
	for(int i=1;i<=t;i++){
		ll x2=fast_pow(x1,2,n);
		if(x2==1&&x1!=1&&x1!=n-1) return true;
		x1=x2;
	}
	if(x1%n!=1) return true;
	return false;
}
int miller_rabin(ll x,int s){
	if(x<2) return 0;
	if(x==2) return 1;
	if(x%2==0) return 0;
	for(int i=1;i<=s;i++){
		ll a=rand()%(x-1)+1;
		if(witness(a,x)) return 0;
	}
	return 1;
}
int main(){
	ll x;
	while(scanf("%d",&N)!=EOF){
		int cnt=0;
		while(N--){
			scanf("%lld",&x);
			int s=50;
			cnt+=miller_rabin(x,s);
		}
		printf("%d\n",cnt);
	}
	return 0;
}
