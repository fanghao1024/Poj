#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int max_n=2e5+10;

ll dp[max_n][20];
int M,L,l;
ll D,x,t;
char ch[10];
void update(ll val){
	dp[l][0]=val;
	for(int i=1;i<=log2(l);i++){
		dp[l][i]=max(dp[l][i-1],dp[l-(1<<(i-1))][i-1]);
	}
}
ll query(int len){
	int k=log2(len);
	return max(dp[l][k],dp[l-len+(1<<k)][k]);
}
int main(){
	scanf("%d %lld",&M,&D);
	t=l=0;
	while(M--){
		scanf("%s",ch);
		if(ch[0]=='A'){
			scanf("%lld",&x);
			x=(x+t)%D;
			l++;
			update(x);
		}else{
			scanf("%d",&L);
			t=query(L);
			printf("%lld\n",t);
		}
	}
	return 0;
}
