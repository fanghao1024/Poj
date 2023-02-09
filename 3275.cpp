#include <iostream>
#include<stdio.h>
#include<bitset>
using namespace std;

const int max_n=1010;
bitset<max_n> rec[max_n];
int main() {
	int N,M;
	scanf("%d %d",&N,&M);
	int X,Y;
	for(int i=0;i<M;i++){
		scanf("%d %d",&X,&Y);
		rec[X].set(Y);
	}

	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			if(rec[j][i]){
				rec[j]|=rec[i];
			}
		}
	}
	int ans=0;
	
	for(int i=1;i<=N;i++){
		ans+=rec[i].count();
	}

	printf("%d\n",N*(N-1)/2-ans);
	return 0;
}