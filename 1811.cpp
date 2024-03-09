#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long ll;
int T;
ll N;
ll fast_pow(ll a,ll u,ll n){
	ll res=1;
	while(u){
		if(u&1) res=(res*a)%n;
		a=(a*a)%n;
		u>>=1;
	}
	return res;
}
bool witness(ll a,ll n){
	ll u=n-1,t=0;
	while(u&1==0){
		t++;
		u>>=1;
	}
	ll x1,x2;
	x1=fast_pow(a,u,n);
	for(int i=1;i<=t;i++){
		x2=fast_pow(x1,2,n);
		if(x2==1&&x1!=1&&x1!=n-1) return true;
		x1=x2;
	}
	if(x1%(n-1)!=1) return true;
	return false;
}
bool miller_rabin(ll n,int s){
	if(n<2) return false;
	if(n==2) return true;
	if(!(n&1)) return false;
	for(int t=1;t<=s;t++){
		ll a=rand()%(n-1)+1;
		if(witness(a,n)) return false;
	}
	return true;
}
ll mul(ll a,ll b,ll m){
	a%=m;
	b%=m;
	ll res=0;
	while(b){
		if(b&1){
			res+=a;
			if(res>=m) res-=m;
		}
		a<<=1;
		if(a>=m) a-=m;
		b>>=1;
	}
	return res;
}

ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}
ll pollard_rho(ll c,ll n){
	ll i=1,k=2;
	ll x=rand()%n;
	ll y=x;
	do{
		i++;
		ll d=gcd(n+y-x,n);
		if(d>1&&d<n) return d;
		if(i==k) y=x,k<<=1;
		x=(mul(x,x,n)+n-c)%n;
	}while(y!=x);
	return n;
	
}
ll rho(ll n){
	if(miller_rabin(n,50)) return n;
	ll t=n;
	while(t>=n) t=pollard_rho(rand()%(n-1)+1,n);
	ll a=rho(t);
	ll b=rho(n/t);
	return a<b?a:b;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&N);
		if(miller_rabin(N,50)){
			printf("Prime\n");
		}else{
			printf("%I64d\n",rho(N));
		}
	}
	return 0;
}
