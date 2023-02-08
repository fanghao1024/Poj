#include<stdio.h>
#include<algorithm>
using namespace std;

int L,N,M;
int dis[50010];
bool C(int mid){
	int distance=0;
	int count=0;
	for(int i=0;i<N;i++){
		if(dis[i]-distance>=mid){
			count++;
			distance=dis[i];
		}
		if(count>=N-M) return true;
		if(i+1-count>M) return false;
	}
	if(count>=N-M){
		return true;
	}else{
		return false;
	}
	
}

int main(){
	scanf("%d %d %d",&L,&N,&M);
	for(int i=0;i<N;i++){
		scanf("%d",&dis[i]);
	}
	sort(dis,dis+N);
	int lb=1;
	int ub=1000000001;
	while(ub>lb+1){
		int mid=(lb+ub)/2;
		//printf("%d-%d-%d\n",lb,mid,ub);
		if(C(mid)){
			lb=mid;
		}else{
			ub=mid;
		}
	}
	lb=lb<L?lb:L;
	printf("%d\n",lb);
	return 0;
}
