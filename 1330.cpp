#include <iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

int N;
const int max_n=10010;
int num[max_n];
int par[max_n];
bool vis[max_n];
void init(){
	for(int i=1;i<=N;i++)
		par[i]=i;
	memset(vis,0,sizeof(vis));
}
int solve(int a,int b){
	vis[a]=1;
	while(par[a]!=a){
		a=par[a];
		vis[a]=1;
	}
	while((!vis[b])&&(par[b]!=b)){
		vis[b]=1;
		b=par[b];
	}
	return b;
}
int main() {
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		
		init();
		int a,b;
		for(int i=0;i<N-1;i++){
			scanf("%d %d",&a,&b);
			par[b]=a;
		}
		scanf("%d %d",&a,&b);
		printf("%d\n",solve(a,b));
	}
	return 0;
}