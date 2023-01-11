#include<stdio.h>
#include<algorithm>
using namespace std;

int N,M;
int num[100010];
int stacks[100010];

bool C(int mid){
	if(num[0]>mid) return false;
	int index=1;
	stacks[0]=num[0];
	for(int i=1;i<N;i++){
		if(num[i]>mid) return false;
		if(index+N-i>=M){
			if(num[i]+stacks[index-1]<=mid){
				stacks[index-1]+=num[i];
			}else{
				stacks[index++]=num[i];
			}
		}else{
			stacks[index++]=num[i];
		}
		if(index>M) return false;
	}
	return true;
}
int main(){
	scanf("%d %d",&N,&M);
	int lb=0;
	for(int i=0;i<N;i++){
		scanf("%d",&num[i]);
		lb=lb>num[i]?lb:num[i];
	}
	int ub=1000000000;
	lb-=1;
	while(ub>lb+1){
		int mid=(lb+ub)/2;
		
		if(C(mid)){
			ub=mid;
		}else{
			lb=mid;
		}
	}
	printf("%d\n",ub);
	return 0;
}
