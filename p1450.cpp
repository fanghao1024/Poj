#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e5+10;
typedef long long ll;
ll f[max_n],c[4],d[4],s;
int N;
int main(){
	for(int i=0;i<4;i++) scanf("%lld",&c[i]);
	scanf("%d",&N);
	f[0]=1;
	for(int i=0;i<4;i++){
		for(int j=c[i];j<=1e5;j++){
			f[j]+=f[j-c[i]];
		}
	}
	while(N--){
		for(int i=0;i<4;i++) scanf("%lld",&d[i]);
		scanf("%lld",&s);
		ll ans=f[s];
		for(int i=1;i<=15;i++){
			ll k=0,num=0;
			for(int j=0;j<4;j++){
				if(i&(1<<j)) k+=c[j]*(d[j]+1),num++;
			}
			ll mark=1;
			if(num%2) mark=-1;
			if(s>=k) ans+=mark*f[s-k];
		}
		printf("%lld\n",ans);
		
	}
	return 0;
}
