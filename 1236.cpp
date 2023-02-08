#include<stdio.h>
#include<string.h>
#include<stack>
#include<algorithm>
using namespace std;

const int max_n=105;
const int max_e=10005;
int head[max_n];
int fdn[max_n];
int low[max_n];
int indegree[max_n];
int outdegree[max_n];
int belong[max_n];
bool ins[max_n];
struct Edge{
	int to;
	int nxt;
}edge[max_e];
int N,cnt,num,id;
stack<int> si;
void tarjan(int u){
	fdn[u]=low[u]=++num;
	si.push(u);
	ins[u]=1;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(!fdn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else{
			if(ins[v]){
				low[u]=min(low[u],fdn[v]);
			}
		}
	}
	if(low[u]==fdn[u]){
		int v;
		//printf("%d &&&& %d\n",u,id);
		do{
			v=si.top();
			si.pop();
			ins[v]=0;
			belong[v]=id;
			//printf("%d !!!! %d===%d\n",v,belong[v],id);
		}while(v!=u);
		id++;
	}
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
int main(){
	scanf("%d",&N);
	int x;
	cnt=0;
	num=0;
	id=1;
	memset(head,-1,sizeof(head));
	memset(fdn,0,sizeof(fdn));
	memset(ins,0,sizeof(ins));
	memset(indegree,0,sizeof(indegree));
	memset(outdegree,0,sizeof(outdegree));
	for(int i=1;i<=N;i++){
		while(scanf("%d",&x)&&x){
			add_edge(i,x);
		}
	}
	for(int i=1;i<=N;i++){
		if(!fdn[i]){
			tarjan(i);
		}
	}
	//for(int i=1;i<=N;i++) printf("%d **** %d\n",i,belong[i]);
	for(int i=1;i<=N;i++){
		for(int j=head[i];j!=-1;j=edge[j].nxt){
			int v=edge[j].to;
			//printf("%d-%d:%d^^^^%d\n",i,v,belong[i],belong[v]);
			if(belong[i]!=belong[v]){
				//printf("%d~~~%d\n",belong[i],belong[v]);
				outdegree[belong[i]]++;
				indegree[belong[v]]++;
			}
		}
	}
	if(id==2){
		printf("1\n0\n");
		return 0;
	}
	int ans1=0;
	int ans2=0;
	for(int i=1;i<id;i++){
		//printf("%d===%d##%d\n",i,indegree[i],outdegree[i]);
		if(!indegree[i]) ans1++;
		if(!outdegree[i]) ans2++;
	}
	printf("%d\n",ans1);
	printf("%d\n",max(ans1,ans2));
	return 0;
}
