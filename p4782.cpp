#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e6+10;
int head[max_n<<1],cnt,low[max_n<<1],num[max_n<<1],sccno[max_n<<1],st[max_n<<1],top,dfn,tot;
struct Edge{
	int to,nxt;
}edge[max_n<<1];
void init(){
	memset(head,-1,sizeof(head));
	memset(low,0,sizeof(low));
	memset(num,0,sizeof(num));
	memset(sccno,0,sizeof(sccno));
	cnt=top=dfn=tot=0;
}
void add_edge(int x,int y){
	edge[cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt++;
}
int N,M;
void tarjan(int u){
	num[u]=low[u]=++dfn;
	st[top++]=u;
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
	if(low[u]==num[u]){
		tot++;
		while(1){
			int v=st[--top];
			sccno[v]=tot;
			if(v==u) break;
		}
	}
}
bool sat(){
	for(int i=1;i<=2*N;i++){
		if(!num[i]) tarjan(i);
	}
	for(int i=1;i<=N;i++){
		if(sccno[i]==sccno[i+N]) return false;
	}
	return true;
}
int main(){
	init();
	scanf("%d %d",&N,&M);
	int a,va,b,vb,nota,notb;
	while(M--){
		scanf("%d %d %d %d",&a,&va,&b,&vb);
		nota=va^1;notb=vb^1;
		add_edge(a+nota*N,b+vb*N);
		add_edge(b+notb*N,a+va*N);
	}
	if(sat()){
		printf("POSSIBLE\n");
		for(int i=1;i<=N;i++){
			if(i-1) printf(" ");
			printf("%d",sccno[i]>sccno[i+N]);
		}
	}else{
		printf("IMPOSSIBLE\n");
	}
	return 0;
}
