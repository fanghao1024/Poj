#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=2010;
char s[max_n];
int ans[max_n][max_n];
int sz,last;
struct Tree{
	int son[26];
	int father;
	int len;
}tr[max_n<<1];
void newnode(int _len){
	tr[++sz].len=_len;
	tr[sz].father=-1;
	memset(tr[sz].son,0,sizeof(tr[sz].son));
}
void init(){
	sz=-1,last=0;
	newnode(0);
}
void Insert(int x){
	newnode(tr[last].len+1);
	int p=last,cur=sz;
	while(p!=-1&&!tr[p].son[x]){
		tr[p].son[x]=cur;
		p=tr[p].father;
	}
	if(p==-1){
		tr[cur].father=0;
	}else{
		int q=tr[p].son[x];
		if(tr[q].len==tr[p].len+1){
			tr[cur].father=q;
		}else{
			newnode(tr[p].len+1);
			int nq=sz;
			memcpy(tr[nq].son,tr[q].son,sizeof(tr[q].son));
			tr[nq].father=tr[q].father;
			tr[cur].father=tr[q].father=nq;
			while(p>=0&&tr[p].son[x]==q){
				tr[p].son[x]=nq;
				p=tr[p].father;
			}
		}
	}
	last=cur;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		memset(ans,0,sizeof(ans));
		scanf("%s",s);
		int n=strlen(s);
		for(int i=0;i<n;i++){
			init();
			ans[i][i]=1;Insert(s[i]-'a');
			for(int j=i+1;j<n;j++){
				Insert(s[j]-'a');
				//if(i==j) printf("i:%d,j:%d,a[%d][%d]=%d\n",i,j=1,i,j-1,ans[i][j-1]);
				ans[i][j]=ans[i][j-1]+tr[last].len-tr[tr[last].father].len;
			}
		}
		int Q,L,R;
		scanf("%d",&Q);
		while(Q--){
			scanf("%d %d",&L,&R);
			printf("%d\n",ans[--L][--R]);
		}
	}
	return 0;
}
