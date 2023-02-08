#include<stdio.h>
#include<string.h>


const int max_n=100010;
int N;
int A[max_n],B[max_n];
int tree[max_n];

#define lowbit(x) x&(-x)

void update(int index,int x){
	while(index<=N){
		tree[index]+=x;
		index+=lowbit(index);
	}
}
int sum(int index){
	int res=0;
	while(index>0){
		res+=tree[index];
		index-=lowbit(index);
	}
	return res;
}
int main(){
	while(scanf("%d",&N)&&N){
		for(int i=1;i<=N;i++){
			scanf("%d %d",&A[i],&B[i]);
		} 
		memset(tree,0,sizeof(tree));
		for(int i=1;i<=N;i++){
			update(A[i],1);
			update(B[i]+1,-1);
		}
		for(int i=1;i<=N;i++){
			if(i!=1) printf(" ");
			printf("%d",sum(i));
		}
		printf("\n");
	}
	return 0;
}
