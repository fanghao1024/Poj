#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

const int max_n=1024;
const int inf=0x3f3f3f3f;
int indeg[26],outdeg[26];
string s[max_n];
int g[26][26],N,par[26],tot,head[26],ans[max_n];
void init(){
	memset(indeg,0,sizeof(indeg));
	memset(outdeg,0,sizeof(outdeg));
	memset(g,0,sizeof(g));
	memset(head,-1,sizeof(head));
	for(int i=0;i<26;i++) par[i]=i;
	tot=0;
}
int find(int x){
	if(x!=par[x]) par[x]=find(par[x]);
	return par[x];
}

struct Edge{
	int to,nxt;
	int id;
	bool flag;
}edge[max_n<<1];
void add_edge(int x,int y,int id){
	edge[tot].to=y;
	edge[tot].id=id;
	edge[tot].nxt=head[x];
	edge[tot].flag=false;
	head[x]=tot++;
}
void dfs(int u){
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		if(!edge[i].flag){
			edge[i].flag=1;
			dfs(edge[i].to);
			ans[tot++]=edge[i].id;
			//printf("%d:%s\n",tot-1,s[ans[tot-1]]);
		}
	}
}
int main(){
	int T;
	//scanf("%d",&T);
	cin>>T;
	while(T--){
		//scanf("%d",&N);
		cin>>N;
		init();
		for(int i=0;i<N;i++){
			//scanf("%s",s[i]);
			cin>>s[i];
			int u=s[i][0]-'a';
			//int v=s[i][strlen(s[i])-1]-'a';
			int v=s[i][s[i].size()-1]-'a';
			if(find(u)!=find(v)){
				par[find(u)]=find(v);
			}
			g[u][v]++;
			outdeg[u]++;
			indeg[v]++;
		}
		bool flag=true;
		int ru=0,chu=0,cnt=0;
		int st=inf;
		for(int i=0;i<26;i++){
			if(find(i)==i&&(indeg[i]+outdeg[i]>0)) cnt++;
			if(indeg[i]!=outdeg[i]){
				if(outdeg[i]==indeg[i]+1){
					chu++;
					st=i;
				}
				else if(outdeg[i]==indeg[i]-1){
					ru++;
				}
				else flag=false;
			}
		}
		
		if(flag&&cnt==1&&((ru==1&&chu==1)||(ru==0&&chu==0))){
			sort(s,s+N);
			for(int i=N-1;i>=0;i--){
				int u=s[i][0]-'a';
				int v=s[i][s[i].size()-1]-'a';
				add_edge(u,v,i);
				if(chu) continue;
				st=min(st,min(u,v));
			}
			tot=0;
			dfs(st);
			
			//printf("%s",s[ans[tot-1]]);
			cout<<s[ans[tot-1]];
			for(int i=tot-2;i>=0;i--){
				//printf(".%s",s[ans[i]]);
				cout<<"."<<s[ans[i]];
			}
			//printf("\n");
			cout<<endl;
		}else{
			cout<<"***"<<endl;
			//printf("***\n");
		}
	}
	return 0;
}
