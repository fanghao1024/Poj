#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int N,cnt,root,S,ans,K;
const int max_n=10010;
int head[max_n],s[max_n],f[max_n],dep[max_n],d[max_n];
bool vis[max_n];
struct Edge{
	int to,w;
	int nxt;
}edge[max_n<<1];

void add_edge(int x,int y,int w){
	edge[cnt].to=y;
	edge[cnt].w=w;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void get_root(int u,int fa){
	s[u]=1;
	f[u]=0;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v!=fa&&!vis[v]){
			get_root(v,u);
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
	dep[0]=0;
	d[u]=dis;
	get_dep(u,0);
	sort(dep+1,dep+1+dep[0]);
	int l=1,r=dep[0],sum=0;
	while(l<r){
		if(dep[l]+dep[r]<K){
			l++;
		}else{
			if(dep[l]+dep[r]>K){
				r--;
			}else{
				if(dep[l]==dep[r]){
					sum+=(r-l+1)*(r-l)/2;
					break;
				}
				int tl=l,tr=r;
				while(dep[tl]==dep[l]) tl++;
				while(dep[tr]==dep[r]) tr--;
				sum+=(tl-l)*(r-tr);
				l=tl;
				r=tr;
			}
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
			get_root(v,0);
			solve(root);
		}
	}
}
int main(){
	while(scanf("%d",&N)&&N){
		int x,y;
		memset(head,-1,sizeof(head));
		cnt=0;
		for(int i=1;i<=N;i++){
			while(scanf("%d",&x)&&x){
				scanf("%d",&y);
				add_edge(i,x,y);
				add_edge(x,i,y);
			}
		}
		f[0]=0x7fffffff;
		while(scanf("%d",&K)&&K){
			memset(vis,0,sizeof(vis));
			root=ans=0;
			S=N;
			get_root(1,0);
			solve(root);
			if(ans){
				printf("AYE\n");
			}else{
				printf("NAY\n");
			}
		}
		printf(".\n");
	}
	return 0;
}
