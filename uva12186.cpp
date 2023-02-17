#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int max_n=100010;
int N,T,cnt;
int head[max_n];
struct Edge{
	int to,nxt;
}edge[max_n];
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
int dp[max_n];
void dfs(int u){
	if(head[u]==-1){
		dp[u]=1;
		return ;
	}
	dp[u]=0;
	vector<int> rec;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		dfs(v);
		rec.push_back(dp[v]);
	}
	sort(rec.begin(),rec.end());
	int c=(rec.size()*T-1)/100+1;
	for(int i=0;i<c;i++) dp[u]+=rec[i];
}
int main(){
	while(scanf("%d %d",&N,&T)!=EOF){
		if(!N&&!T) break;
		int x;
		cnt=0;
		memset(head,-1,sizeof(head));
		for(int i=1;i<=N;i++){
			scanf("%d",&x);
			add_edge(x,i);
		}
		dfs(0);
		printf("%d\n",dp[0]);
	}
	return 0;
}
