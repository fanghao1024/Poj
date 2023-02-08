#include<stdio.h>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=805;
ll x[max_n];
ll y[max_n];

int main(){
	int T,n;
	scanf("%d",&T);
	for(int case_num=1;case_num<=T;case_num++){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%lld",&x[i]);
		}
		for(int i=0;i<n;i++){
			scanf("%lld",&y[i]);
		}
		sort(x,x+n);
		sort(y,y+n);
		long long ans=0;
		for(int i=0;i<n;i++){
			ans+=x[i]*y[n-1-i];
		}
		printf("Case #%d: %lld\n",case_num,ans);
		
	}
	return 0;
}
