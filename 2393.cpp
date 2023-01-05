#include<stdio.h>

int cost[10010];
int delivery[10010];

int main(){
	int N,S;
	scanf("%d %d",&N,&S);
	for(int i=0;i<N;i++){
		scanf("%d %d",&cost[i],&delivery[i]);

	}
	long long ans=0;
	int index=0;
	int flag=0;
	while(index<N){
		while((index+flag<N)&&(cost[index+flag]-cost[index])>=S*flag){
			ans+=delivery[index+flag]*(cost[index]+S*flag);
			//printf("%d %lld\n",delivery[index+flag]*(cost[index]+S*flag),ans);
			flag+=1;
		}
		index+=flag;
		flag=0;
	}
	printf("%lld\n",ans);
	return 0;
}
