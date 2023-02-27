#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;

const int max_n=1024;
bool vis[max_n];
int M,N;

int main(){
	
	scanf("%d %d",&M,&N);
	queue<int> q;
	memset(vis,0,sizeof(vis));
	int x,ans=0;
	while(N--){
		scanf("%d",&x);
		if(vis[x]) continue;
		ans++;
		if(q.size()<M) q.push(x);
		else{
			vis[q.front()]=0;
			q.pop();
			q.push(x);
		}
		vis[x]=1;
	}
	printf("%d\n",ans);
	return 0;
}
