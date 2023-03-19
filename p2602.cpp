#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=15;
int num[max_n];
int dp[max_n];
int ten[max_n];
ll a,b;
ll cnta[max_n],cntb[max_n];
void init(){
	ten[0]=1;
	for(int i=1;i<=12;i++) dp[i]=dp[i-1]*10+ten[i-1],ten[i]=ten[i-1]*10;
}
void solve(ll x,ll* cnt){
	int len=0;
	while(x){
		num[++len]=x%10;
		x/=10;
	}
	for(int i=len;i>=1;i--){
		for(int j=0;j<=9;j++) cnt[j]+=dp[i-1]*num[i];
		for(int j=0;j<num[i];j++) cnt[j]+=ten[i-1];
		ll num2=0;
		for(int j=i-1;j>=1;j--){
			num2=num2*10+num[j];
		}
		cnt[num[i]]+=num2+1;
		cnt[0]-=ten[i-1];
	}
}
int main(){
	scanf("%lld %lld",&a,&b);
	init();
	solve(a-1,cnta);solve(b,cntb);
	for(int i=0;i<=9;i++){
		if(i) printf(" ");
		printf("%lld",cntb[i]-cnta[i]);
	}
	printf("\n");
	return 0;
}


