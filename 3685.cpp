#include<stdio.h>

typedef long long ll;
ll N,M;
ll compute(ll i,ll j){
	return i*i+100000*i+j*j-100000*j+i*j;
}
ll check(ll mid){
	ll res=0;
	for(ll j=1;j<=N;j++){
		ll l=1;
		ll r=N;
		ll ans=0;
		while(l<=r){
			//printf("%lld===%lld\n",l,r);
			ll lr=((r-l)>>1)+l;
			//printf("======%lld\n",compute(lr,j));
			if(compute(lr,j)==mid){
				ans=lr-1;
				break;
			}else{
				if(compute(lr,j)<=mid){
					l=lr+1;
					ans=lr;
				}else{
					r=lr-1;
				}
			}
			
		}
		res+=ans;
		if(res>=M) return false;
	}
	return true;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lld %lld",&N,&M);
		ll lb=-1000000000000;
		ll ub=1000000000000;
		while(ub>lb+1){
			ll mid=((ub-lb)>>1)+lb;
			//printf("%lld\n",mid);
			
			//true则mid低估,false则高估mid,等号包含在true中
			if(check(mid)){
				lb=mid;
			}else{
				ub=mid;
			}
		}
		printf("%lld\n",lb);
	}
	return 0;
}
