#include<stdio.h>

const int max_n=10005;
int d[max_n];
int N;

int main(){
	int w,Q,pos;
	int ans=0;
	scanf("%d",&N);	
	for(int i=1;i<=N;i++){
		scanf("%d %d",&w,&Q);
		d[i]=w;
		for(int j=0;j<Q;j++){
			scanf("%d",&pos);
			d[i]=d[i]>(d[pos]+w)?d[i]:(d[pos]+w);
		}
		ans=ans>d[i]?ans:d[i];
	}
	printf("%d\n",ans);
	return 0;
}
