#include <iostream>
#include <stdio.h>
#include<set>
using namespace std;
int N,M;
const int max_n=1010;
int rec[max_n];
int ranks[max_n];
void init(int n){
	for(int i=1;i<=n;i++){
		rec[i]=i;
		ranks[i]=1;
	}
}
int find(int x){
	if(x!=rec[x]){
		rec[x]=find(rec[x]);
	}
	return rec[x];
}
void unite(int x,int y){
	int a=find(x);
	int b=find(y);
	if(a!=b){
		if(ranks[a]>ranks[b]){
			rec[b]=a;
		}else{
			rec[a]=b;
			if(ranks[a]==ranks[b]){
				ranks[b]++;
			}
		}
	}
}
int main() {
	while(scanf("%d",&N)&&N){
		scanf("%d",&M);
		int x,y;
		init(N);
		while(M--){
			scanf("%d %d",&x,&y);
			unite(x,y);
		}
		int ans=0;
		for(int i=1;i<=N;i++){
			if(i==find(i)) ans++;
		}
		printf("%d\n",ans-1);
	}
	return 0;
}