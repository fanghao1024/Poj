#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;

const int max_n=50010;
const int inf=2147483647;

int N,M,cnt;
int num[max_n];

struct Node{
	int son[2];
	int val,pri,size,num;
}node[max_n*50];
int newNode(int val){
	node[++cnt].val=val;
	node[cnt].son[0]=node[cnt].son[1]=0;
	node[cnt].pri=rand();
	node[cnt].size=1;
	node[cnt].num=1;
	return cnt;
}
void init(){
	cnt=0;
	node[0].size=node[0].num=0;
	node[0].son[0]=node[0].son[1]=0;
}
struct Treap{
	int root;
	void update(int p){
		node[p].size=node[node[p].son[0]].size+node[node[p].son[1]].size+node[p].num;
	}
	void ToRight(int& p){
		int lson=node[p].son[0];
		node[p].son[0]=node[lson].son[1];
		node[lson].son[1]=p;
		update(p);
		update(lson);
		p=lson;
	}
	void ToLeft(int& p){
		int rson=node[p].son[1];
		node[p].son[1]=node[rson].son[0];
		node[rson].son[0]=p;
		update(p);
		update(rson);
		p=rson;
	}
	void insert(int& p,int val){
		if(!p){
			p=newNode(val);
			return ;
		}
		node[p].size++;
		if(node[p].val==val){
			node[p].num++;
			return ;
		}
		if(node[p].val>val){insert(node[p].son[0],val);if(node[node[p].son[0]].pri>node[p].pri) ToRight(p);}
		if(node[p].val<val){insert(node[p].son[1],val);if(node[node[p].son[1]].pri>node[p].pri) ToLeft(p);}	
	}
	void del(int& p,int val){
		if(!p) return ;
		if(node[p].val==val){
			if(node[p].num>1){node[p].num--;node[p].size--;return ;}
			int lson=node[p].son[0],rson=node[p].son[1];
			if(!lson||!rson) p=lson+rson;
			else
			{
				if(node[lson].pri>node[rson].pri){
					ToRight(p);
					del(p,val);
				}else{
					ToLeft(p);
					del(p,val);
				}
			}	
		}else{
			node[p].size--;
			del(node[p].son[node[p].val<val],val);
		}
	}
	int queryRank(int u,int val){
		if(!u) return 0;
		if(node[u].val==val) return node[node[u].son[0]].size;
		if(node[u].val>val) return queryRank(node[u].son[0],val);
		else return node[node[u].son[0]].size+node[u].num+queryRank(node[u].son[1],val);
	}
	int Pre(int u,int val){
		if(!u) return -inf;
		if(node[u].val>=val) return Pre(node[u].son[0],val);
		else return max(node[u].val,Pre(node[u].son[1],val));
	}
	int Nxt(int u,int val){
		if(!u) return inf;
		if(node[u].val<=val) return Nxt(node[u].son[1],val);
		else return min(node[u].val,Nxt(node[u].son[0],val));
	}
	
}tr[max_n<<2];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;};
void build(int p,int pl,int pr){
	tr[p].root=0;
	for(int i=pl;i<=pr;i++){
		tr[p].insert(tr[p].root,num[i]);
	}
	if(pl==pr) return ;
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
}
int queryRank(int L,int R,int val,int p,int pl,int pr){
	if(L>pr||R<pl) return 0;
	if(L<=pl&&pr<=R) return tr[p].queryRank(tr[p].root,val);
	int mid=(pl+pr)>>1;
	int ans=0;
	ans+=queryRank(L,R,val,ls(p),pl,mid);
	ans+=queryRank(L,R,val,rs(p),mid+1,pr);
	return ans;
}
int queryValue(int L,int R,int val,int p,int pl,int pr){
	int l=0,r=1e8;
	int ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(queryRank(L,R,mid,p,pl,pr)+1<=val){
			ans=mid;
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	return ans;
}
void change(int pos,int val,int p,int pl,int pr){
	if(pos<pl||pos>pr) return ;
	tr[p].del(tr[p].root,num[pos]);
	tr[p].insert(tr[p].root,val);
	if(pl==pr) return ;
	int mid=(pl+pr)>>1;
	change(pos,val,ls(p),pl,mid);
	change(pos,val,rs(p),mid+1,pr);
}
int queryPre(int L,int R,int val,int p,int pl,int pr){
	if(L>pr||R<pl) return -inf;
	if(L<=pl&&pr<=R) return tr[p].Pre(tr[p].root,val);
	int ans;
	int mid=(pl+pr)>>1;
	ans=queryPre(L,R,val,ls(p),pl,mid);
	ans=max(ans,queryPre(L,R,val,rs(p),mid+1,pr));
	return ans;
}
int queryNxt(int L,int R,int val,int p,int pl,int pr){
	if(L>pr||R<pl) return inf;
	if(L<=pl&&pr<=R) return tr[p].Nxt(tr[p].root,val);
	int ans;
	int mid=(pl+pr)>>1;
	ans=queryNxt(L,R,val,ls(p),pl,mid);
	ans=min(ans,queryNxt(L,R,val,rs(p),mid+1,pr));
	return ans;
}
int main(){
	srand(time(0));
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++){
		scanf("%d",&num[i]);
	}
	init();
	build(1,1,N);
	int opt,l,r,k,pos;
	while(M--){
		scanf("%d",&opt);
		switch (opt) {
		case 1:
			scanf("%d %d %d",&l,&r,&k);
			printf("%d\n",queryRank(l,r,k,1,1,N)+1);
			break;
		case 2:
			scanf("%d %d %d",&l,&r,&k);
			printf("%d\n",queryValue(l,r,k,1,1,N));
			break;
		case 3:
			scanf("%d %d",&pos,&k);
			change(pos,k,1,1,N);
			num[pos]=k;
			break;
		case 4:
			scanf("%d %d %d",&l,&r,&k);
			printf("%d\n",queryPre(l,r,k,1,1,N));
			break;
		case 5:
			scanf("%d %d %d",&l,&r,&k);
			printf("%d\n",queryNxt(l,r,k,1,1,N));
			break;
		}
	}
	return 0;
}
