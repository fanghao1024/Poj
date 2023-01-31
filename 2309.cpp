#include<stdio.h>

int lowbit(int x){
	return x&(-x);
}
int main(){
	int N;
	scanf("%d",&N);
	int x;
	for(int i=0;i<N;i++){
		scanf("%d",&x);
		printf("%d %d\n",x-lowbit(x)+1,x+lowbit(x)-1);
	}
	return 0;
}
