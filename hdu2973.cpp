#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int max_n=3e6+10;

bool vis[max_n];
ll prime[max_n];
int cnt;
int ans[max_n];
void init(){
	memset(vis,0,sizeof(vis));
	vis[0]=vis[1]=true;
	cnt=0;
	for(int i=2;i<max_n;i++){
		if(!vis[i]){
			prime[cnt++]=i;
		}
		for(int j=0;j<cnt;j++){
			if((ll)i*prime[j]>=max_n) break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
	for(int i=1;i<=1e6;i++){
		ans[i]=ans[i-1]+(1-vis[3*i+7]);
	}
}
int main(){
	init();	
	int T;
	scanf("%d",&T);
	int x;
	while(T--){
		scanf("%d",&x);
		printf("%d\n",ans[x]);
	}
	return 0;
}
