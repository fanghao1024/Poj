#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
struct Intervel{
	int s;
	int e;
	int w;
}intervel[1010];
int p[1010];
int dp[1010];

bool cmp(const Intervel &a,const Intervel &b){
	if(a.e!=b.e){
		return a.e<b.e;
	}else{
		return a.s<b.s;
	}
}

int main(){
	int N,M,R;
	scanf("%d %d %d",&N,&M,&R);
	for(int i=0;i<M;i++){
		scanf("%d %d %d",&intervel[i].s,&intervel[i].e,&intervel[i].w);
		intervel[i].e+=R;
		if(intervel[i].e>N){
			intervel[i].e=N;
		}
	}
	sort(intervel,intervel+M,cmp);
	memset(p,-1,sizeof(p));
	p[0]=0;
	for(int i=1;i<M;i++){
		for(int j=i-1;j>=0;j--){
			if(intervel[j].e<=intervel[i].s){
				p[i]=j;
				break;
			}
		}

	}
	memset(dp,-1,sizeof(dp));
	dp[0]=intervel[0].w;
	for(int i=1;i<M;i++){
		if(p[i]>=0){
			dp[i]=max(dp[i-1],dp[p[i]]+intervel[i].w);
		}else{
			dp[i]=max(dp[i-1],intervel[i].w);
		}
		

	}
	printf("%d\n",dp[M-1]);
	return 0;
}
