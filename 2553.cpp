#include<stdio.h>
#include<string.h>
#include<stack>
#include<algorithm>
using namespace std;

const int max_n=5005;
const int max_e=20010;
int head[max_n];
bool ins[max_n];
int fdn[max_n];
int low[max_n];
int rec[max_n];
int degree[max_n];
bool ans[max_n];
int V,E;
struct Edge{
	int to;
	int nxt;
}edge[max_e];
int cnt;
stack<int> si;
int num;
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
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
	if(fdn[u]==low[u]){
		int v;
		do{
			v=si.top();
			si.pop();
			ins[v]=0;
			rec[v]=u;
		}while(v!=u);
	}
}
int main(){
	while(scanf("%d",&V)&&V){
		scanf("%d",&E);
		cnt=0;
		memset(head,-1,sizeof(head));
		memset(fdn,0,sizeof(fdn));
		memset(ins,0,sizeof(ins));
		memset(degree,0,sizeof(degree));
		memset(ans,0,sizeof(ans));
		while(!si.empty()){
			si.pop();
		}
		int x,y;
		for(int i=0;i<E;i++){
			scanf("%d %d",&x,&y);
			add_edge(x,y);
		}
		num=0;
		for(int i=1;i<=V;i++){
			if(!fdn[i]){
				tarjan(i);
			}
		}
		
		for(int i=1;i<=V;i++){
			for(int j=head[i];j!=-1;j=edge[j].nxt){
				int v=edge[j].to;
				if(low[v]!=low[i]){
					degree[low[i]]++;
				}
			}
		}
		int count=0;
		for(int i=1;i<=V;i++){
			if(!degree[low[i]]){
				if(count) printf(" ");
				printf("%d",i);
				count++;
			}
		}
		printf("\n");
	}
	return 0;
}
