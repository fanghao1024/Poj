#include<cstdio>
#include<algorithm>
using namespace std;

const int max_n=100010;

int T,N,M,tot,cnt;
int num[max_n],temp[max_n],rt[max_n];
struct Tr{
	int num,son[2];
}tr[max_n*40];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void build(int& p,int l,int r){
	p=++cnt;
	tr[p].num=0;
	tr[p].son[0]=tr[p].son[1]=0;
	if(l==r) return ;
	int mid=(l+r)>>1;
	build(tr[p].son[0],l,mid);
	build(tr[p].son[1],mid+1,r);
}
void update(int& i,int j,int l,int r,int val){
	i=++cnt;
	tr[i]=tr[j];
	tr[i].num++;
	if(l==r) return ;
	int mid=(l+r)>>1;
	if(val<=mid) update(tr[i].son[0],tr[j].son[0],l,mid,val);
	else update(tr[i].son[1],tr[j].son[1],mid+1,r,val);
}
int query(int i,int j,int l,int r,int k){
	if(l==r) return tr[j].num-tr[i].num;
	int ans=0;
	int mid=(l+r)>>1;
	if(k<=mid) ans+=query(tr[i].son[0],tr[j].son[0],l,mid,k);
	else{
		ans+=tr[tr[j].son[0]].num-tr[tr[i].son[0]].num;
		ans+=query(tr[i].son[1],tr[j].son[1],mid+1,r,k);
	}
	return ans;
}
int main(){
	scanf("%d",&T);
	for(int caseNo=1;caseNo<=T;caseNo++){
		scanf("%d %d",&N,&M);
		for(int i=1;i<=N;i++) scanf("%d",&num[i]),temp[i]=num[i];
		sort(temp+1,temp+1+N);
		tot=unique(temp+1,temp+1+N)-temp-1;
		cnt=0;
		build(rt[0],1,tot);
		for(int i=1;i<=N;i++){
			update(rt[i],rt[i-1],1,tot,lower_bound(temp+1,temp+1+tot,num[i])-temp);
		}
		printf("Case %d:\n",caseNo);
		int l,r,h;
		while(M--){
			scanf("%d%d%d",&l,&r,&h);
			l++,r++;
			int k=upper_bound(temp+1,temp+1+tot,h)-temp-1;
			if(k==0) printf("0\n");
			else printf("%d\n",query(rt[l-1],rt[r],1,tot,k));
		}
	}
	return 0;
}
