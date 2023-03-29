#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=55;
typedef long long ll;

ll P[max_n];
int N;
bool zero;
void Insert(ll x){
	for(int i=max_n-1;i>=0;i--){
		if((x>>i)==1){
			if(P[i]==0){
				P[i]=x;
				return ;
			}
			else{
				x^=P[i];
			}
		}
	}
	zero=true;
}
ll Max(){
	ll res=0;
	for(int i=max_n-1;i>=0;i--) res=max(res,res^P[i]);
	return res;
}
int main(){
	ll x;
	scanf("%d",&N);
	for(int i=1;i<=N;i++){
		scanf("%lld",&x);
		Insert(x);
	}
	ll ans=Max();
	printf("%lld\n",ans);
	return 0;
}
