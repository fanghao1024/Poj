#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

int N,Q;
const int max_n=50010;
int num[max_n];
int mintree[max_n];
int maxtree[max_n];

int lowbit(int x){
	return x&(-x);
}
void updateMaxtree(int x,int d){
	
	while(x<=N){
		maxtree[x]=d;
		for(int i=1;i<lowbit(x);i<<=1){
			maxtree[x]=max(maxtree[x],maxtree[x-i]);
		}
		x+=lowbit(x);
	}
}
void updateMintree(int x,int d){
	
	while(x<=N){
		mintree[x]=d;
		for(int i=1;i<lowbit(x);i<<=1){
			mintree[x]=min(mintree[x],mintree[x-i]);
		}
		x+=lowbit(x);
	}
}
int queryMax(int L,int R){
	int ans=0;
	while(L<=R){
		ans=max(ans,num[R]);
		R--;
		while(R-lowbit(R)>=L){
			ans=max(ans,maxtree[R]);
			R-=lowbit(R);
		}
	}
	return ans;
}
int queryMin(int L,int R){
	int ans=1000100;
	while(L<=R){
		ans=min(ans,num[R]);
		R--;
		while(R-lowbit(R)>=L){
			ans=min(ans,mintree[R]);
			R-=lowbit(R);
		}
	}
	return ans;
}

int main(){
	
	scanf("%d %d",&N,&Q);
	memset(maxtree,0,sizeof(maxtree));
	for(int i=1;i<=N;i++) mintree[i]=1000100;
	for(int i=1;i<=N;i++){
		scanf("%d",&num[i]);
		updateMaxtree(i,num[i]);
		updateMintree(i,num[i]);
	}
	int A,B;
	while(Q--){
		scanf("%d %d",&A,&B);
		//printf("~~~%d %d\n",queryMax(A,B),queryMin(A,B));
		printf("%d\n",queryMax(A,B)-queryMin(A,B));
	}
	
	
	return 0;
}
