#include<stdio.h>
#include<algorithm>
using namespace std;

int N,C;
int dis[100010];
bool con(int mid){
	int last=0;
	for(int i=1;i<C;i++){
		int cur=last+1;
		while(cur<N&&dis[cur]-dis[last]<mid){
			cur++;
		}
		if(cur==N) return false;
		last=cur;
	}
	return true;
}
int main(){
	scanf("%d %d\n",&N,&C);
	for(int i=0;i<N;i++){
		scanf("%d",&dis[i]);
	}
	sort(dis,dis+N);

	int lb=0;
	int ub=1000000001;
	while(ub>lb+1){
		int mid=(ub+lb)/2;
		if(con(mid)){
			lb=mid;
		}else{
			ub=mid;
		}
	}
	printf("%d\n",lb);
	return 0;
}
