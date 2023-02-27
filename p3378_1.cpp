#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int max_n=1e6+100;

int fa[max_n],v[max_n],l[max_n],r[max_n],d[max_n];
int root;
int merge(int x,int y){
	if(!x) return y;
	if(!y) return x;
	if(v[x]>v[y]) swap(x,y);
	r[x]=merge(r[x],y);
	fa[r[x]]=x;
	if(d[l[x]]<d[r[x]]) swap(l[x],r[x]);
	d[x]=d[r[x]]+1;
	return x;
}
void pop(){
	fa[l[root]]=l[root];
	fa[r[root]]=r[root];
	root=merge(l[root],r[root]);
}
int main(){
	int n,ops,x;
	root=0;
	int cnt=0;
	d[0]=-1;
	scanf("%d",&n);
	while(n--){
		scanf("%d",&ops);
		switch(ops){
			case 1:
				scanf("%d",&v[++cnt]);
				l[cnt]=r[cnt]=d[cnt]=0;
				fa[cnt]=cnt;
				root=merge(root,cnt);
				break;
			case 2:
				printf("%d\n",v[root]);
				break;
			case 3:
				pop();
				break;
		}
	}
	return 0;
}
