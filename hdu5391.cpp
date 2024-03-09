#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long ll;

int T;
ll N;
ll fast_pow(ll x,ll y,ll m){
	ll res=1;
	while(y){
		if(y&1) res=(res*x)%m;
		x=(x*x)%m;
		y>>=1;
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
bool miller_rabin(ll n){
	if(n<2) return false;
	if(n==2) return true;
	if(n%2==0) return false;
	for(int i=1;i<=50&&i<n;i++){
		ll a=rand()%(n-1)+1;
		if(witness(a,n)) return false;
	}
	return true;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&N);
		if(miller_rabin(N)){
			printf("%lld\n",N-1);
		}else{
			if(N==4) printf("2\n");
			else printf("0\n");
		}
	}
	return 0;
}
