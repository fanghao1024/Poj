#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long ll;
const int max_n=1e5+10;
const ll MOD=998244353;
int two[max_n],three[max_n];
int T,N,M;

int main(){
	scanf("%d",&T);
	int x,y,z;
	while(T--){
		scanf("%d %d",&N,&M);
		memset(two,0,sizeof(two));
		memset(three,0,sizeof(three));
		int min2=M,min3=M;
		while(M--){
			scanf("%d %d %d",&x,&y,&z);
			if(z==2){
				two[x]++;two[y+1]--;
			}else{
				three[x]++;three[y+1]--;
			}
		}
		
		for(int i=1;i<=N;i++){
			two[i]+=two[i-1];
			min2=min(two[i],min2);
			three[i]+=three[i-1];
			min3=min(three[i],min3);
		}
		ll ans=1;
		while(min2--){
			ans=(ans*2)%MOD;
		}
		while(min3--){
			ans=(ans*3)%MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

