#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=105;
const int max_T=10010+120*120;
const int inf=0x3f;
int N,T,maxv;
int V[max_n],C[max_n],num[max_T];
int dp1[max_T],dp2[120*120];
int main(){
	scanf("%d %d",&N,&T);
	maxv=-1;
	for(int i=0;i<N;i++) scanf("%d",&V[i]),maxv=max(maxv,V[i]);
	for(int i=0;i<N;i++) scanf("%d",&C[i]);
	maxv=maxv*maxv;
	memset(dp1,0x3f,sizeof(dp1));
	memset(dp2,0x3f,sizeof(dp2));
	dp1[0]=0;
	for(int i=0;i<N;i++){
		memset(num,0,sizeof(num));
		for(int j=V[i];j<=T+maxv;j++){
			if(dp1[j]>dp1[j-V[i]]+1&&num[j-V[i]]<C[i]){
				dp1[j]=dp1[j-V[i]]+1;
				num[j]=num[j-V[i]]+1;
			}
		}
	}
	dp2[0]=0;
	for(int i=0;i<N;i++){
		for(int j=V[i];j<=maxv;j++){
			dp2[j]=min(dp2[j],dp2[j-V[i]]+1);
		}
	}
	int ans=0x3f3f3f3f;
	for(int i=0;i<=maxv;i++){
		ans=min(ans,dp1[i+T]+dp2[i]);
	}
	if(ans==0x3f3f3f3f) ans=-1;
	printf("%d\n",ans);
	return 0;
}
