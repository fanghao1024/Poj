#include<stdio.h>
#include<bitset>
#include<string.h>
using namespace std;

bitset<1002> rec[10005];
bool rep[10005];
int N,Q;
int main(){
	scanf("%d",&N);
	int K;
	int x;
	memset(rep,0,sizeof(rep));
	for(int i=1;i<=N;i++){
		scanf("%d",&K);
		for(int j=0;j<K;j++){
			scanf("%d",&x);
			if(rec[x][i]==1){
				rep[x]=1;
			}else{
				rec[x][i]=1;
			}
		}
	}
	scanf("%d",&Q);
	int y;
	while(Q--){
		scanf("%d %d",&x,&y);
		if((rec[x]&rec[y]).count()){
			printf("Yes\n");
		}else{
			printf("No\n");
		}
		/*
		if(x==y){
			if(rep[x]){
				printf("Yes\n");
			}else{
				printf("No\n");
			}
		}else{
			
		  }*/
	}
	return 0;
}
