#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define lc tr[i].son[0]
#define rc tr[i].son[1]
#define Lc tr[j].son[0]
#define Rc tr[j].son[1]


typedef long long ll;
const int max_n=100005;
int N,M,cnt,tot,n,m;
//int a[max_n];
int rt[max_n];
struct Tr{
	ll sum;
	ll lazy;
	int son[2];
}tr[max_n*30];

void pushup(int p){
	tr[p].sum=tr[tr[p].son[0]].sum+tr[tr[p].son[1]].sum;
}
void push_up(int i){tr[i].sum=tr[lc].sum+tr[rc].sum;}


void build(int& p,int pl,int pr){
	p=++cnt;
	tr[p].lazy=0;
	if(pl==pr){
		//tr[p].sum=(ll)a[pl];
		scanf("%lld",&tr[p].sum);
		//tr[p].son[0]=tr[p].son[1]=0;
		return ;
	}
	int mid=(pl+pr)>>1;
	build(tr[p].son[0],pl,mid);
	build(tr[p].son[1],mid+1,pr);
	pushup(p);
}

void update(int& i,int j,int l,int r,int L,int R,int val){
	i=++cnt;
	tr[i]=tr[j];
	tr[i].sum+=1ll*val*(R-L+1);
	if(L<=l&&r<=R){
		tr[i].lazy+=val;
		return ;
	}
	if(R<l||L>r) return ;
	int mid=(l+r)>>1;
	if(L<=mid) update(tr[i].son[0],tr[j].son[0],l,mid,L,R,val);
	if(R>mid) update(tr[i].son[1],tr[j].son[1],mid+1,r,L,R,val);
	//if(R<=mid) update(tr[i].son[0],tr[j].son[0],l,mid,L,R,val);
	//else if(L>mid) update(tr[i].son[1],tr[j].son[1],mid+1,r,L,R,val);
	//else{
	//	update(tr[i].son[0],tr[j].son[0],l,mid,L,mid,val);
	//	update(tr[i].son[1],tr[j].son[1],mid+1,r,mid+1,R,val);
	//}
}

ll query(int p,int pl,int pr,int L,int R,ll tag){
	if(L<=pl&&pr<=R) return tr[p].sum+1ll*(pr-pl+1)*tag;
	ll ans=0;
	int mid=(pl+pr)>>1;
	if(L<=mid) ans+=query(tr[p].son[0],pl,mid,L,R,tag+tr[p].lazy);
	if(R>mid) ans+=query(tr[p].son[1],mid+1,pr,L,R,tag+tr[p].lazy);
	return ans;
	//if(R<=mid) return query(tr[p].son[0],pl,mid,L,R,tag+tr[p].lazy);
	//else if(L>mid) return query(tr[p].son[1],mid+1,pr,L,R,tag+tr[p].lazy);
	//else return query(tr[p].son[0],pl,mid,L,mid,tag+tr[p].lazy)+query(tr[p].son[1],mid+1,pr,mid+1,R,tag+tr[p].lazy);
	
}

int main(){
	while(scanf("%d%d",&N,&M)!=EOF){
		//for(int i=1;i<=N;i++) scanf("%lld",&a[i]),a[i];
		cnt=tot=0;
		tr[0].sum=0;
		build(rt[0],1,N);
		char ops[3];
		int l,r,d,t;
		while(M--){
			scanf("%s",ops);
			switch (ops[0]) {
			case 'C':
				scanf("%d%d%d",&l,&r,&d);
				tot++;
				update(rt[tot],rt[tot-1],1,N,l,r,d);
				break;
			case 'Q':
				scanf("%d%d",&l,&r);
				printf("%lld\n",query(rt[tot],1,N,l,r,0));
				break;
			case 'H':
				scanf("%d %d %d",&l,&r,&t);
				printf("%lld\n",query(rt[t],1,N,l,r,0));
				break;
			case 'B':
				scanf("%d",&t);
				tot=t;
				cnt=rt[t+1]-1;
				break;
			}
		}
	}
	return 0;
}
 

