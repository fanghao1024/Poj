#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=1e5+10;

ll A,B,C;
int N,M;
ll t[max_n],b[max_n];
ll calc1(ll p){
	ll x=0,y=0;
	for(int i=1;i<=M;i++){
		if(b[i]<p) x+=p-b[i];
		else y+=b[i]-p;
	}
	if(A<B) return A*min(x,y)+B*(y-min(x,y));
	else return B*y;
}
ll calc2(ll p){
	ll sum=0;
	for(int i=1;i<=N;i++){
		if(t[i]<p) sum+=p-t[i];
	}
	return C*sum;
}
int main(){
	scanf("%lld %lld %lld",&A,&B,&C);
	scanf("%d %d",&N,&M);
	for(int i=1;i<=N;i++) scanf("%lld",&t[i]);
	for(int i=1;i<=M;i++) scanf("%lld",&b[i]);
	sort(t+1,t+1+N);sort(b+1,b+1+M);
	if(C==1e16){
		printf("%lld\n",calc1(t[1]));
		return 0;
	}
	ll ans=1e16;
	ll l=t[1],r=t[N];
	while(r-l>2){
		ll d=(r-l)/3;
		ll mid1=l+d,mid2=r-d;
		if(calc1(mid1)+calc2(mid1)>calc1(mid2)+calc2(mid2)){
			l=mid1;
		}else{
			r=mid2;
		}
	}
	for(ll i=l;i<=r;i++){
		ans=min(ans,calc1(i)+calc2(i));
	}
	printf("%lld\n",ans);
	return 0;
}
