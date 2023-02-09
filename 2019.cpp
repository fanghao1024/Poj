#include <iostream>
#include<stdio.h>
#include<cmath>
#include<algorithm>
using namespace std;

int N,B,K;
int num[260][260];
int maxtree[260][260][10];
int mintree[260][260][10];
int logValue[260];
void initLog(){
	logValue[0]=-1;
	for(int i=1;i<=250;i++){
		logValue[i]=(i&(i-1))?logValue[i-1]:logValue[i-1]+1;
	}
}
void build(){
	for(int k=1;k<=N;k++){
		for(int i=1;i<=N;i++){
			mintree[k][i][0]=maxtree[k][i][0]=num[k][i];
		}
	}
	int k=logValue[N];
	for(int m=1;m<=N;m++){
		for(int j=1;j<=k;j++){
			for(int i=1;i<=N+1-(1<<j);i++){
				maxtree[m][i][j]=max(maxtree[m][i][j-1],maxtree[m][i+(1<<(j-1))][j-1]);
				mintree[m][i][j]=min(mintree[m][i][j-1],mintree[m][i+(1<<(j-1))][j-1]);
			}
		}
	}
}


int RMQMax(int L,int R,int m){
	int k=logValue[R-L+1];
	return max(maxtree[m][L][k],maxtree[m][R-(1<<k)+1][k]);
}

int RMQMin(int L,int R,int m){
	int k=logValue[R-L+1];
	return min(mintree[m][L][k],mintree[m][R-(1<<k)+1][k]);
}

int main() {
	
	scanf("%d %d %d",&N,&B,&K);
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			scanf("%d",&num[i][j]);
		}
	}
	initLog();
	build();
	int x,y;
	while(K--){
		scanf("%d %d",&x,&y);
		int maxValue=-1;
		int minValue=0x3f3f3f3f;
		for(int i=x;i<x+B;i++){
			maxValue=max(maxValue,RMQMax(y, y+B-1, i));
			minValue=min(minValue,RMQMin(y, y+B-1, i));
		}
		printf("%d\n",maxValue-minValue);
	}
	return 0;
}