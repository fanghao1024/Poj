#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

const int max_n=25*25;
const int inf=0x3f3f3f3f;
int T,N,D,M,cnt;
int head[max_n<<1],dep[max_n<<1],g[max_n<<1],pre[(max_n*max_n)<<4],now[max_n<<1];
char ch[25];
struct Edge{
	int to,nxt;
	int cap,flow;
}edge[(max_n*max_n)<<4];
void add_edge(int x,int y,int c){
	edge[cnt].to=y;
	edge[cnt].cap=c;
	edge[cnt].flow=0;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
void adde(int x,int y,int c){
	add_edge(x,y,c);
	add_edge(y,x,0);
}
void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
}
int getpos(int i,int j){
	return M*i+j+1;
}
void bfs(int t){
	memset(g,0,sizeof(g));
	memset(dep,0,sizeof(dep));
	queue<int> q;
	q.push(t);
	dep[t]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		g[dep[u]]++;
		for(int i=head[u];i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(!dep[v]){
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
}
int isap(int s,int t,int n){
	bfs(t);
	int ans=0;
	int u=s;
	int d;
	memcpy(now,head,sizeof(head));
	while(dep[s]<=n){
		if(u==s) d=inf;
		int i=now[u];
		for(;i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(dep[v]+1==dep[u]&&edge[i].cap>edge[i].flow){
				pre[v]=i;
				now[u]=i;
				d=min(d,edge[i].cap-edge[i].flow);
				u=v;
				if(u==t){
					while(u!=s){
						int e=pre[u];
						edge[e].flow+=d;
						edge[e^1].flow-=d;
						u=edge[e^1].to;
					}
					ans+=d;
					d=inf;	
				}
				break;
			}
		}
		if(i==-1){
			if(!--g[dep[u]]) break;
			int mindep=n+5;
			for(int j=head[u];j!=-1;j=edge[j].nxt){
				int v=edge[j].to;
				if(edge[j].cap>edge[j].flow&&dep[v]<mindep) mindep=dep[v];
			}
			dep[u]=mindep+1;
			now[u]=head[u];
			g[dep[u]]++;
			if(u!=s) u=edge[pre[u]^1].to;
		}
	}
	return ans;
}
int main(){
	scanf("%d",&T);
	int s,t;
	for(int caseNo=1;caseNo<=T;caseNo++){
		init();
		int sum=0;
		scanf("%d %d",&N,&D);
		for(int i=0;i<N;i++){
			scanf("%s",ch);
			if(!i){
				M=strlen(ch);
				s=0,t=2*N*M+1;
			}
			
			for(int j=0;j<M;j++){
				int nums=ch[j]-'0';
				if(nums>0){
					int ids=getpos(i,j);
					adde(ids,ids+N*M,nums);
					if(i-D<0||i+D>=N||j-D<0||j+D>=M){
						adde(ids+N*M,t,inf);
					}else{
						for(int h=0;h<N;h++){
							for(int w=0;w<M;w++){
								int ids2=getpos(h,w);
								if(ids2==ids) continue;
								if(abs(i-h)+abs(j-w)<=D) adde(ids+N*M,ids2,inf);
							}
						}
					}
				}
				
			}
		}
		for(int i=0;i<N;i++){
			scanf("%s",ch);
			for(int j=0;j<M;j++){
				if(ch[j]=='L'){
					adde(s,getpos(i,j),1);
					sum++;
				}
			}
		}
		
		int ans=sum-isap(s,t,t+1);
		if(ans==0) printf("Case #%d: no lizard was left behind.\n",caseNo);
		else if(ans==1) printf("Case #%d: %d lizard was left behind.\n",caseNo,ans);
		else printf("Case #%d: %d lizards were left behind.\n",caseNo,ans);
	}
	return 0;
}
