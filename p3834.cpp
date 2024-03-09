#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=2e5+10;

int a[max_n],b[max_n],root[max_n];
struct Tree{
	int l,r;
	int val;
}tree[max_n<<5];
int N,M,cnt,ind;
int update(int p,int pl,int pr,int pos){
	int rt=++ind;
	tree[rt].l=tree[p].l;
	tree[rt].r=tree[p].r;
	tree[rt].val=tree[p].val+1;
	int mid=(pl+pr)>>1;
	if(pl<pr){
		if(pos<=mid){
			tree[rt].l=update(tree[p].l,pl,mid,pos);
		}else{
			tree[rt].r=update(tree[p].r,mid+1,pr,pos);
		}
	}
	return rt;
}
int query(int u,int v,int pl,int pr,int k){
	if(pl==pr) return pl;
	int sum=tree[tree[v].l].val-tree[tree[u].l].val;
	int mid=(pl+pr)>>1;
	if(k<=sum) return query(tree[u].l,tree[v].l,pl,mid,k);
	else return query(tree[u].r,tree[v].r,mid+1,pr,k-sum);
}
int main(){
	scanf("%d %d",&N,&M);
	for(int i=1;i<=N;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+1+N);
	cnt=unique(b+1,b+1+N)-b-1;
	memset(tree,0,sizeof(tree));
	ind=0;
	for(int i=1;i<=N;i++){
		int pos=lower_bound(b+1,b+1+cnt,a[i])-b;
		root[i]=update(root[i-1],1,cnt,pos);
	}
	int l,r,k;
	while(M--){
		scanf("%d %d %d",&l,&r,&k);
		int temp=query(root[l-1],root[r],1,cnt,k);
		printf("%d\n",b[temp]);
	}
	return 0;
}
