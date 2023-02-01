#include<stdio.h>
#include<algorithm>
using namespace std;

int N;
int num[100010];

int categorical(int m,int n){
	int p=1,q=1;
	for(int i=1;i<=n;i++){
		p*=(m-i+1);
		q*=i;
	}
	return p/q;
}
int C(int mid){
	int ans=0;
	for(int i=0;i<N;i++){
		ans+=num+N-lower_bound(num+i+1,num+N,num[i]+mid);
	}
	return ans<=categorical(N,2)/2;
}
int main(){
	while(scanf("%d",&N)!=EOF){
		for(int i=0;i<N;i++){
			scanf("%d",&num[i]);
		}
		sort(num,num+N);
		int lb=0;
		int ub=num[N-1]-num[0];
		while(ub>lb+1){
			int mid=(ub+lb)>>1;
			if(C(mid)){
				ub=mid;
			}else{
				lb=mid;
			}
		}
		printf("%d\n",ub);
	}	
	return 0;
}
