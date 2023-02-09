#include <iostream>
#include<stdio.h>
#include<cmath>
#include<algorithm>
using namespace std;

int N,K;
const int max_n=200010;
int num[max_n];
int rec[max_n][20];

void build(){
	for(int i=1;i<=N;i++) rec[i][0]=num[i];
	//for(int i=1;i<=N;i++) printf("***** %d\n",rec[i][0]);
	int k=int(log(N+0.0)/log(2.0));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=N+1-(1<<j);i++){
			rec[i][j]=max(rec[i][j-1],rec[i+(1<<(j-1))][j-1]);
		}
	}
}
int RMQ(int L,int R){
	int k=int(log(R-L+1.0)/log(2.0));
	//printf("@@@ %d %d %d\n",L,R,k);
	//printf("%d===%d\n",rec[L][k],rec[R-(1<<k)+1][k]);
	return max(rec[L][k],rec[R-(1<<k)+1][k]);
}
bool ok(int mid){
	int ans=0;
	int lens=N/mid;
	for(int i=0;i<mid;i++){
		ans+=RMQ(lens*i+1,(i+1)*lens);
	}
	//printf("^^^^^%d\n",ans);
	return ans>K;
}
int main() {
	while(scanf("%d %d",&N,&K)){
		if(N==-1&&K==-1){
			break;
		}
		for(int i=1;i<=N;i++) scanf("%d",&num[i]);
		build();
		int lb=1,ub=N;
		int ans=-1;
		while(ub>=lb){
			int mid=(ub+lb)/2;
			//printf("===%d\n",mid);
			if(ok(mid)){
				//printf("~~~%d\n",mid);
				ub=mid-1;
				ans=mid;
			}else{
				lb=mid+1;
			}
		}
		if(ans==-1){
			printf("-1\n");
		}else{
			printf("%d\n",ans);
		}
		
	}
	return 0;
}