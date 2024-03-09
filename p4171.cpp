#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=110<<1;

int head[max_n],cnt,low[max_n],num[max_n],st[max_n],tot,top,dfn,N,M,sccno[max_n];
struct Edge{
	int to,nxt;
}edge[2048];
void init(){
	memset(head,-1,sizeof(head));
	memset(low,0,sizeof(low));
	memset(num,0,sizeof(num));
	memset(sccno,0,sizeof(sccno));
	cnt=tot=top=dfn=0;
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
int cal(char* s){
	//int k=s[0]=='m'?0:1;
	int res=0;
	for(int i=1;i<strlen(s);i++){
		res=res*10+s[i]-'0';
	}
	return res;
}
char s1[10],s2[10];
void tarjan(int u){
	st[top++]=u;
	num[u]=low[u]=++dfn;
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		if(!num[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!sccno[v]){
			low[u]=min(low[u],num[v]);
		}
	}
	if(num[u]==low[u]){
		tot++;
		while(1){
			int v=st[--top];
			sccno[v]=tot;
			if(v==u) break;
		}
	}
}
bool two_sat(){
	for(int i=1;i<=2*N;i++){
		if(!num[i]) tarjan(i);
	}
	for(int i=1;i<=N;i++){
		if(sccno[i]==sccno[i+N]) return false;
	}
	return true;
}
int main(){
	int T,x,y;
	scanf("%d",&T);
	while(T--){
		init();
		scanf("%d %d",&N,&M);
		while(M--){
			scanf("%s %s",s1,s2);
			x=cal(s1);
			y=cal(s2);
			if(s1[0]=='m'&&s2[0]=='m'){
				add_edge(x+N,y);add_edge(y+N,x);
			}
			else if(s1[0]=='m'&&s2[0]=='h'){
				add_edge(x+N,y+N);
				add_edge(y,x);
			}
			else if(s1[0]=='h'&&s2[0]=='m'){
				add_edge(x,y);
				add_edge(y+N,x+N);
			}
			else if(s1[0]=='h'&&s2[0]=='h'){
				add_edge(x,y+N);add_edge(y,x+N);
			}
		}
		if(two_sat()) printf("GOOD\n");
		else printf("BAD\n");
	}
	return 0;
}
