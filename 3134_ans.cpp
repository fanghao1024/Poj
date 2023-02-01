#include<stdio.h>
#include<cmath>

const int max_n=1005;
int e[max_n];
int N,dep;
bool dfs(int d){
	if(e[d]==N) return true;
	if(d>=dep) return false;
	if((e[d]<<(dep-d))<N) return false;
	for(int i=0;i<=d;i++){
		e[d+1]=e[d]+e[i];
		if(dfs(d+1)) return true;
		e[d+1]=abs(e[d]-e[i]);
		if(dfs(d+1)) return true;
	}
	return false;
}
int inastar(){
	e[0]=1;
	for(dep=0;;dep++){
		if(dfs(0)){
			return dep;
		}
	}
}
int main(){
	while(scanf("%d",&N)&&N){
		printf("%d\n",inastar());
	}
	return 0;
}
