#include<stdio.h>
#include<string.h>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

const int max_n=102;
const int max_e=10005;
int head[max_n];
struct Edge{
	int to;
	int nxt;
}edge[max_e];
int cnt;
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt;
	cnt++;
}
bool matrix[max_n][max_n];
bool vis[max_n];
bool ans[max_n];
int dfn[max_n];
int low[max_n];
int nums;
int root;

void tarjan(int u,int fa){
	vis[u]=1;
	dfn[u]=low[u]=++nums;
	int count=0;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa) continue;
		if(!vis[v]){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				count++;
				if(count>1||u!=root){
					ans[u]=1;
				}
			}
		}else{
			low[u]=min(low[u],dfn[v]);
		}
	}
	
}
int main(){
	int N;
	while(scanf("%d",&N)&&N){
		getchar();
		memset(head,-1,sizeof(head));
		memset(matrix,0,sizeof(matrix));
		memset(vis,0,sizeof(vis));
		memset(ans,0,sizeof(ans));
		string s;
		cnt=0;
		while(getline(cin,s)){
			if(s=="0") break;
			int index=0;
			int num=0;
			while(index<s.size()&&s[index]!=' '){
				num*=10;
				num+=s[index]-'0';
				index++;
			}
			while(index<s.size()){
				while(s[index]==' ') index++;
				int v=0;
				while(index<s.size()&&s[index]!=' '){
					v*=10;
					v+=s[index]-'0';
					index++;
				}
				if(v>0&&!matrix[num][v]){
					add_edge(num,v);
					matrix[num][v]=1;
					add_edge(v,num);
					matrix[v][num]=1;
				}
			}
		}
		nums=0;
		for(int i=1;i<=N;i++){
			if(!vis[i]){
				root=i;
				tarjan(i,i);
			}
		}
		int res=0;
		for(int i=1;i<=N;i++){
			if(ans[i]){
				res++;
			}
		}
		cout<<res<<endl;
	}
	return 0;
}
