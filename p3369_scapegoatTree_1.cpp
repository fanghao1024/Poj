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
	int tot;
	int siz;
	int val;
	int del;
}tr[max_n];
int N,opt,x,root=0;

void InitNode(int u){
	tr[u].l=tr[u].r=0;
	tr[u].tot=tr[u].siz=tr[u].del=1;
}
void Update(int u){
	tr[u].siz=tr[tr[u].l].siz+tr[tr[u].r].siz+tr[u].del;
	tr[u].tot=tr[tr[u].l].tot+tr[tr[u].r].tot+1;
}
bool notbalance(int u){
	if((double)tr[u].siz*alpha<=(double)max(tr[tr[u].l].siz,tr[tr[u].r].siz)) return true;
	return false;
}
void inorder(int u){
	if(!u) return ;
	inorder(tr[u].l);
	if(tr[u].del) order[++cnt]=u;
	else tree_stack[++top]=u;
	inorder(tr[u].r);
}
void build(int l,int r,int& u){
	int mid=(l+r)>>1;
	u=order[mid];
	if(l==r){InitNode(u);return ;}
	if(l<mid) build(l,mid-1,tr[u].l);
	if(l==mid) tr[u].l=0;
	build(mid+1,r,tr[u].r);
	Update(u);
}
void rebuild(int& u){
	cnt=0;
	inorder(u);
	if(!cnt) u=0;
	else build(1,cnt,u);
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
int Kth(int k){
	int u=root;
	while(u){
		if(tr[tr[u].l].siz+1==k&&tr[u].del) return tr[u].val;
		if(tr[tr[u].l].siz+tr[u].del>=k) u=tr[u].l;
		else{
			k-=tr[tr[u].l].siz+tr[u].del;
			u=tr[u].r;
		}
	}
	return tr[u].val;
}
void Del_k(int& u,int k){
	tr[u].siz--;
	if(tr[u].del&&tr[tr[u].l].siz+1==k){
		tr[u].del=0;
		return ;
	}
	if(tr[tr[u].l].siz+tr[u].del>=k) Del_k(tr[u].l,k);
	else Del_k(tr[u].r,k-tr[tr[u].l].siz-tr[u].del);
}
void Delete(int x){
	Del_k(root,Rank(root,x)+1);
	if(tr[root].tot*alpha>tr[root].siz) rebuild(root);
}
int main(){
	for(int i=max_n-1;i>=1;i--) tree_stack[++top]=i;
	scanf("%d",&N);
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
			printf("%d\n",Kth(x));
			break;
		case 5:
			printf("%d\n",Kth(Rank(root,x)));
			break;
		case 6:
			printf("%d\n",Kth(Rank(root,x+1)+1));
			break;
		}
	}
	return 0;
}
