#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=5e4+10;


int N,cnt,head[max_n],d[max_n],ans[max_n],num,minnum;
struct Edge{
	int to,nxt;
}edge[max_n<<1];
void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
	num=0;
	minnum=N+1;
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void dfs(int u,int fa){
	d[u]=1;
	int temp=0;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa) continue;
		dfs(v,u);
		d[u]+=d[v];
		temp=max(temp,d[v]);
	}
	temp=max(temp,N-d[u]);
	if(minnum>temp){
		num=0;
		ans[num++]=u;
		minnum=temp;
	}
	else if(minnum==temp) ans[num++]=u;
}
int main(){
	int x,y;
	while(scanf("%d",&N)!=EOF){
		init();
		for(int i=1;i<N;i++){
			scanf("%d %d",&x,&y);
			add_edge(x,y);
			add_edge(y,x);
		}
		dfs(1,0);
		sort(ans,ans+num);
		for(int i=0;i<num;i++){
			if(i) printf(" ");
			printf("%d",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
