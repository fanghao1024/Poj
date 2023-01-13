#include<stdio.h>
#include<vector>
using namespace std;

typedef long long ll;
vector<ll> res;
int main(){
	ll N;
	scanf("%lld",&N);
	ll l=1,r=1,sums=0;
	ll ans=0;
	while(l*l<=N){
		while(sums<N){
			sums+=r*r;
			r++;
		}
		if(sums==N){
			//printf("%lld",r-l);
			res.push_back(r-l);
			for(ll i=l;i<r;i++){
				res.push_back(i);
				//printf(" %lld",i);
			}
			res.push_back(-1);
			//printf("\n");
			ans++;
			
		}
		sums-=l*l;
		l++;
	}
	if(ans==0){
		printf("0\n");
	}else{
		printf("%lld\n",ans);
		bool flag=false;
		for(int i=0;i<res.size();i++){
			if(res[i]==-1){
				printf("\n");
				flag=false;
			}else{
				if(flag){
					printf(" ");
				}
				printf("%lld",res[i]);
				flag=true;
			}
		}
	}
	return 0;
}
