#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e6+10;

int num[max_n],Max[max_n],Min[max_n],Q[max_n];
int N,K,st,ed;

void getMin(){
	st=0;
	ed=0;
	Q[ed++]=1; //队列存储的是下标
	Min[1]=num[1];
	for(int i=2;i<=N;i++){
		while(st<ed&&num[i]<num[Q[ed-1]]) ed--;
		Q[ed++]=i;
		while(st<ed&&Q[st]<i-K+1) st++;
		Min[i]=num[Q[st]];
	}
}
void getMax(){
	st=0;
	ed=0;
	Q[ed++]=1;
	Max[1]=num[1];
	for(int i=2;i<=N;i++){
		while(st<ed&&num[i]>num[Q[ed-1]]) ed--;
		Q[ed++]=i;
		while(st<ed&&Q[st]<i-K+1) st++;
		Max[i]=num[Q[st]];
	}
}
int main(){
	while(scanf("%d %d",&N,&K)!=EOF){
		for(int i=1;i<=N;i++){
			scanf("%d",num+i);
		}
		getMin();
		getMax();
		for(int i=K;i<=N;i++){
			if(i-K) printf(" ");
			printf("%d",Min[i]);
		}
		printf("\n");
		for(int i=K;i<=N;i++){
			if(i-K) printf(" ");
			printf("%d",Max[i]);
		}
		printf("\n");
	}
	return 0;
}
