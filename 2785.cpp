#include<stdio.h>
#include<algorithm>
using namespace std;

const int max_n=4010;
int A[max_n],B[max_n],C[max_n],D[max_n];
int temp[max_n*max_n];

int main(){
	int N;
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		scanf("%d %d %d %d",&A[i],&B[i],&C[i],&D[i]);
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			temp[i*N+j]=C[i]+D[j];
		}
	}
	long long res=0;
	sort(temp,temp+N*N);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			int nums=A[i]+B[j];
			res+=upper_bound(temp,temp+N*N,-nums)-lower_bound(temp,temp+N*N,-nums);
		}
	}
	printf("%lld\n",res);
	return 0;
}
