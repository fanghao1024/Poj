#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=1e5+10;
const double alpha=0.75;
int tree_stack[max_n],top=0;
int order[max_n],cnt;
struct Tree{
	int l,r;
	int val;
	int tot;
	int siz;
	int del;
}tr[max_n];
int N,opt,x,root=0;
void InitNode(int u){
	tr[u].l=tr[u].r=0;
	tr[u].tot=tr[u].siz=tr[u].del=1;
}
bool notbalance(int u){
	return (double)tr[u].siz*alpha<=(double)max(tr[tr[u].l].siz,tr[tr[u].r].siz);
}
void inorder(int u){
	if(!u) return ;
	inorder(tr[u].l);
	if(tr[u].del) order[++cnt]=u;
	else tree_stack[++top]=u;
	inorder(tr[u].r);
}
void Update(int u){
	tr[u].siz=tr[tr[u].l].siz+tr[tr[u].r].siz+1;
	tr[u].tot=tr[tr[u].l].tot+tr[tr[u].r].tot+1;
}
void build(int pl,int pr,int& u){
	int mid=(pl+pr)>>1;
	u=order[mid];
	if(pl==pr){InitNode(u);return;}
	if(pl<mid) build(pl,mid-1,tr[u].l);
	if(pl==mid) tr[u].l=0;
	build(mid+1,pr,tr[u].r);
	Update(u);
}
void rebuild(int& u){
	cnt=0;
	inorder(u);
	if(cnt) build(1,cnt,u);
	else u=0;
}
void Insert(int& u,int x){
	if(!u){
		u=tree_stack[top--];
		tr[u].val=x;
		InitNode(u);
		return ;
	}
	tr[u].siz++;
	tr[u].tot++;
	if(x>tr[u].val) Insert(tr[u].r,x);
	else Insert(tr[u].l,x);
	if(notbalance(u)) rebuild(u);
}
int Rank(int u,int x){
	if(!u) return 0;
	if(x>tr[u].val) return tr[tr[u].l].siz+tr[u].del+Rank(tr[u].r,x);
	else return Rank(tr[u].l,x);
}
int kth(int k){
	int u=root;
	while(u){
		if(tr[u].del&&tr[tr[u].l].siz+1==k) return tr[u].val;
		else if(tr[tr[u].l].siz>=k) u=tr[u].l;
		else{
			k-=tr[tr[u].l].siz+tr[u].del;
			u=tr[u].r;
		}
	}
	return tr[u].val;
}
void Del_k(int& u,int k){
	tr[u].siz--;
	if(tr[tr[u].l].siz+1==k&&tr[u].del){
		tr[u].del=0;
		return ;
	}
	if(tr[tr[u].l].siz+tr[u].del>=k) Del_k(tr[u].l,k);
	else Del_k(tr[u].r,k-tr[tr[u].l].siz-tr[u].del);
}
void Delete(int x){
	Del_k(root,Rank(root,x)+1);
	if(tr[root].tot*alpha>=tr[root].siz) rebuild(root);
}

int main(){
	scanf("%d",&N);
	for(int i=max_n-1;i>=1;i--) tree_stack[++top]=i;
	while(N--){
		scanf("%d %d",&opt,&x);
		switch (opt) {
		case 1:
			Insert(root,x);
			break;
		case 2:
			Delete(x);
			break;
		case 3:
			printf("%d\n",Rank(root,x)+1);
			break;
		case 4:
			printf("%d\n",kth(x));
			break;
		case 5:
			printf("%d\n",kth(Rank(root,x)));
			break;
		case 6:
			printf("%d\n",kth(Rank(root,x+1)+1));
			break;
		}
	}
	return 0;
}
