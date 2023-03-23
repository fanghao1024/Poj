#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int max_n=1e6+10;

char s[max_n];
int ans;
int tot;
struct Tree{
	int son[26];
	int len,father;
}tr[max_n<<1];
int cnt[max_n<<1],head[max_n<<1];
struct Edge{
	int to,nxt;
}edge[max_n<<2];

void add_edge(int x,int y){
	edge[tot].to=y;
	edge[tot].nxt=head[x];
	head[x]=tot++;
}
int sz,last;
void newnode(int _len){
	tr[++sz].len=_len;
	tr[sz].father=-1;
	memset(tr[sz].son,0,sizeof(tr[sz].son));
}
void init(){
	sz=-1,last=0;
	newnode(0);
	memset(head,-1,sizeof(head));
	tot=0;
}
void Insert(int x){
	newnode(tr[last].len+1);
	int p=last,cur=sz;
	last=cur;
	cnt[cur]=1;
	while(p!=-1&&!tr[p].son[x]){
		tr[p].son[x]=cur;
		p=tr[p].father;
	}
	if(p==-1) tr[cur].father=0;
	else{
		int q=tr[p].son[x];
		if(tr[q].len==tr[p].len+1) tr[cur].father=q;
		else{
			newnode(tr[p].len+1);
			int nq=sz;
			tr[nq].father=tr[q].father;
			memcpy(tr[nq].son,tr[q].son,sizeof(tr[q].son));
			tr[cur].father=tr[q].father=nq;
			while(p>=0&&tr[p].son[x]==q){
				tr[p].son[x]=nq;
				p=tr[p].father;
			}
		}
	}
}
void build(){
	for(int i=1;i<=sz;i++) add_edge(tr[i].father,i);
}
void dfs(int u){
	for(int i=head[u];i!=-1;i=edge[i].nxt){
		int v=edge[i].to;
		dfs(v);
		cnt[u]+=cnt[v];
	}
	if(cnt[u]>1) ans=max(ans,tr[u].len*cnt[u]);
}

int main(){
	scanf("%s",s);
	init();
	int n=strlen(s);
	for(int i=0;i<n;i++){
		Insert(s[i]-'a');
	}
	ans=0;
	build();
	dfs(0);
	printf("%d\n",ans);
	return 0;
}
