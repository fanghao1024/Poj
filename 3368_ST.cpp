#include <iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;

const int max_n=100010;

int N,Q;
int logValue[max_n];
int num[max_n];
int rec[max_n][20];

void initLog(){
	logValue[0]=-1;
	logValue[1]=0;
	for(int i=2;i<max_n;i++){
		if(i&(i-1)){
			logValue[i]=logValue[i-1];
		}else{
			logValue[i]=logValue[i-1]+1;
		}
	}
}
void build(){
	
	rec[1][0]=1;
	for(int i=2;i<=N;i++){
		if(num[i]==num[i-1]){
			rec[i][0]=rec[i-1][0]+1;
		}else{
			rec[i][0]=1;
		}
	}
	int k=logValue[N];
	for(int j=1;j<=k;j++){
		for(int i=1;i<=N+1-(1<<j);i++){
			rec[i][j]=max(rec[i][j-1],rec[i+(1<<(j-1))][j-1]);
		}
	}
}
int query(int L,int R){
	if(L>R) return 0;
	int t=L;
	while((t<=R)&&(t-1)&&(num[t]==num[t-1])){
		t++;
	}
	int choice1=t-L;
	
	int choice2;
	if(t>R){
		choice2=0;
	}else{
		int k=logValue[R-t+1];
		choice2=max(rec[t][k],rec[R-(1<<k)+1][k]);
	} 
	return max(choice1,choice2);
}
int main() {
	initLog();
	while(scanf("%d",&N)&&N){
		scanf("%d",&Q);
		for(int i=1;i<=N;i++){
			scanf("%d",&num[i]);
		}
		build();
		int x,y;
		while(Q--){
			scanf("%d %d",&x,&y);
			printf("%d\n",query(x,y));
		}
	}
	return 0;
}