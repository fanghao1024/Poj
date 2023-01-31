#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int max_m=25;
int N,M;
int S;
int recR[max_m];
int recH[max_m];
int recV[max_m];
int recS[max_m];

void dfs(int dep,int sumS,int sumV,int r,int h){
	if(!dep){
		if(sumV==N&&sumS<S) S=sumS;
		return ;
	}
	if(sumV+recV[dep]>N||sumS+recS[dep]>S||sumS+2*(N-sumV)/r>S) return;
	for(int R=r;R>=dep;R--){
		if(dep==M) sumS=R*R;
		int maxH=min((N-sumV-recV[dep-1])/R/R,h);
		for(int H=maxH;H>=dep;H--){
			dfs(dep-1,sumS+2*R*H,sumV+R*R*H,R-1,H-1);
		}
	}
}
int main(){
	
	recS[0]=0;
	recV[0]=0;
	for(int i=1;i<21;i++){
		recS[i]=recS[i-1]+2*i*i;
		recV[i]=recV[i-1]+i*i*i;
	}
	while(scanf("%d %d",&N,&M)!=EOF){
		S=0x3fffffff;
		dfs(M,0,0,N,N);
		printf("%d\n",S==0x3fffffff?0:S);
	}
	return 0;
}
