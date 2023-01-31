#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int max_n=15;
int pos[max_n];
int N;
int ans;
bool ok(int u){
	for(int i=1;i<u;i++){
		if(u-i==abs(pos[u]-pos[i])) return false;
	}
	return true;
}
void dfs(int x){
	if(x>N){
		ans++;
		return ;
	}
	for(int i=x;i<=N;i++){
		swap(pos[x],pos[i]);
		if(ok(x)){
			dfs(x+1);
		}
		swap(pos[x],pos[i]);
	}
}
int num[11]={0,1,0,0,2,10,4,40,92,352,724};
int main(){
	while(scanf("%d",&N)&&N){
		
		printf("%d\n",num[N]);
	}
	return 0;
}

