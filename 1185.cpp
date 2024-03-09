#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int max_n=105;
const int max_m=13;
const int inf=0x3f3f3f3f;
char ch[20];
int N,M,top,ans;
int cur[max_n],state[70];
int dp[max_n][70][70],num[70];
bool check(int x){
	if(x&(x<<1)) return 0;
	if(x&(x<<2)) return 0;
	return 1;
}
void init(){
	top=0;
	for(int i=0;i<(1<<M);i++){
		if(!check(i)) continue;
		state[top++]=i;
	}
	
}
bool fit(int val,int i){
	if(val&cur[i]) return 0;
	return 1;
}
int count(int x){
	int res=0;
	while(x){
		res++;
		x-=x&(-x);
	}
	return res;
}
void solve(){
	ans=0;
	memset(dp,-1,sizeof(dp));
	for(int i=0;i<top;i++){
		num[i]=count(state[i]);
		if(fit(state[i],1)){
			dp[1][i][0]=num[i];
			ans=max(ans,num[i]); //可能数据就只有一行
		}
	}
	for(int i=2;i<=N;i++){
		for(int x=0;x<top;x++){
			if(!fit(state[x],i)) continue;
			for(int y=0;y<top;y++){
				if(state[x]&state[y]) continue;
				for(int z=0;z<top;z++){
					if(state[x]&state[z]) continue;
					if(dp[i-1][y][z]==-1) continue;
					dp[i][x][y]=max(dp[i][x][y],dp[i-1][y][z]+num[x]);
				}
				if(i==N) ans=max(ans,dp[i][x][y]);
			}
			
		}
	}
}
int main(){
	while(scanf("%d %d",&N,&M)!=EOF){
		init();
		for(int i=1;i<=N;i++){
			scanf("%s",ch+1);
			cur[i]=0;
			for(int j=1;j<=M;j++){
				if(ch[j]=='H') cur[i]+=1<<(M-j);
			}
		}
		solve();
		printf("%d\n",ans);
	}
	return 0;
}

