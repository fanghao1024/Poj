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
		if(ans<=3){
			for(int i=1;i<=N;i++){
				if(i-1) printf(" ");
				printf("%d",pos[i]);
			}
			printf("\n");
		}
		
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

int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++) pos[i]=i;
	ans=0;
	dfs(1);
	printf("%d\n",ans);
	return 0;
}

