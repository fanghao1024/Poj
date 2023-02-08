#include<stdio.h>
#include<vector>
using namespace std;

typedef long long ll;
const ll p_n=34000;
bool is_prime[p_n+1];
vector<ll> prime;
void get_prime(){
	for(int i=2;i<=p_n;i++){
		is_prime[i]=true;
	}
	for(int i=2;i<=p_n;i++){
		if(is_prime[i]){
			prime.push_back(i);
			for(int j=i*2;j<=p_n;j+=i){
				is_prime[j]=false;
			}
		}
	}
}
bool judge_prime(ll x){
	for(int i=0;i<prime.size()&&prime[i]*prime[i]<=x;i++){
		if(x%prime[i]==0){
			return false;
		}
	}
	return true;
}
ll moda(ll p,ll a){
	ll res=1;
	ll temp=p;
	while(temp>0){
		if((temp&1)==1) res=res*a%p;
		a=a*a%p;
		temp>>=1;
	}
	return res;
}
int main(){
	get_prime();
	ll p,a;
	while(scanf("%lld %lld",&p,&a)){
		if(p==0&&a==0){
			break;
		}
		if(judge_prime(p)){
			printf("no\n");
			continue;
		}
		if(moda(p,a)==a){
			printf("yes\n");
		}else{
			printf("no\n");
		}
	}
	return 0;
}
