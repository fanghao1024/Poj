#include<cstdio>
#include <cstring>
#include<algorithm>
using namespace std;

const int max_n=10010;
const int inf=0x7fffffff;
int head[max_n],s[max_n],f[max_n],vis[max_n],dep[max_n],d[max_n];
struct Edge{
	int to,w;
	int nxt;
}edge[max_n<<1];
int N,K,cnt,root,S,ans;

void add_edge(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=w;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void getroot(int u,int fa){
	s[u]=1;
	f[u]=0;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=fa&&!vis[v]){
			getroot(v,u);
			s[u]+=s[v];
			f[u]=max(f[u],s[v]);
		}
	}
	f[u]=max(f[u],S-s[u]);
	if(f[u]<f[root]) root=u;
}
void get_dep(int u,int fa){
	dep[++dep[0]]=d[u];
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=fa&&!vis[v]){
			d[v]=d[u]+edge[i].w;
			get_dep(v,u);
		}
	}
}
int get_sum(int u,int dis){
	d[u]=dis;
	dep[0]=0;
	get_dep(u,0);
	sort(dep+1,dep+1+dep[0]);
	int l=1,r=dep[0],sum=0;
	while(l<r){
		if(dep[r]+dep[l]<=K){
			sum+=r-l;
			l++;
		}else{
			r--;
		}
	}
	return sum;
}
void solve(int u){
	vis[u]=true;
	ans+=get_sum(u,0);
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(!vis[v]){
			ans-=get_sum(v,edge[i].w);
			root=0;
			S=s[v];
			getroot(v,u);
			solve(root);
		}
	}
}
int main(){
	int x,y,w;
	while(scanf("%d %d",&N,&K)){
		if(N==0&&K==0) break;
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
		cnt=0;
		ans=0;
		for(int i=0;i<N-1;i++){
			scanf("%d %d %d",&x,&y,&w);
			add_edge(x,y,w);
			add_edge(y,x,w);
		}
		root=0;
		S=N;
		f[0]=inf;
		getroot(1,0);
		solve(root);
		printf("%d\n",ans);
	}
	return 0;
}
