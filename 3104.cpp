#include<stdio.h>

typedef long long ll;
int n;
ll num[100010];
ll k;
bool C(ll mid){
	ll res=0;

	for(int i=0;i<n;i++){
		if(num[i]<=mid) continue;
		res+=(num[i]-mid+k-2)/(k-1);
		if(res>mid) return false;
	}
	return true;
}
int main(){
	scanf("%d",&n);
	ll ub=0;
	for(int i=0;i<n;i++){
		scanf("%lld",&num[i]);
		ub=ub>num[i]?ub:num[i];
	}
	scanf("%lld",&k);
	if(k==1){
		printf("%d\n",ub);
		
	}
	else{
		ll lb=0;
		while(ub>lb+1){
			ll mid=(ub+lb)/2;
			if(C(mid)){
				ub=mid;
			}else{
				lb=mid;
			}
		}
		printf("%lld\n",ub);
	}
	
	
	return 0;
}
