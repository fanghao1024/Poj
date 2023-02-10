#include<cstdio>
#include<cstdlib>

const int max_n=100005;

struct Tr{
	int ls,rs;
	int pri;
	int id,val;
	int size;
}tr[max_n];
int ops,cnt,root;
void init(){
	cnt=root=0;
	tr[0].ls=tr[0].rs=tr[0].size=0;
}
int newNode(int id,int val){
	cnt++;
	tr[cnt].id=id;
	tr[cnt].val=val;
	tr[cnt].pri=rand();
	tr[cnt].ls=tr[cnt].rs=0;
	tr[cnt].size=1;
	return cnt;
}
void Update(int x){
	tr[x].size=tr[tr[x].ls].size+tr[tr[x].rs].size+1;
}
void Split(int u,int val,int& L,int& R){
	if(!u){L=R=0;return;}
	if(tr[u].val<=val){
		L=u;
		Split(tr[u].rs,val,tr[u].rs,R);
	}else{
		R=u;
		Split(tr[u].ls,val,L,tr[u].ls);
	}
	Update(u);
}
int Merge(int L,int R){
	if(!L||!R){
		return L+R;
	}
	if(tr[L].pri>tr[R].pri){
		tr[L].rs=Merge(tr[L].rs,R);
		Update(L);
		return L;
	}else{
		tr[R].ls=Merge(L,tr[R].ls);
		Update(R);
		return R;
	}
}
void Insert(int id,int val){
	int L,R;
	Split(root,val,L,R);
	root=Merge(Merge(L,newNode(id,val)),R);
}
void Delete(int x){
	int L,R,p;
	Split(root,x,L,R);
	Split(L,x-1,L,p);
	p=Merge(tr[p].ls,tr[p].rs);
	root=Merge(Merge(L,p),R);
}
int kth(int u,int k){
	if(tr[tr[u].ls].size+1==k) return u;
	if(tr[tr[u].ls].size>=k) return kth(tr[u].ls,k);
	return kth(tr[u].rs,k-tr[tr[u].ls].size-1);
}
int FindMax(){
	return kth(root,tr[root].size);
}
int FindMin(){
	return kth(root,1);
}
int main(){
	init();
	int id,val,ans;
	while(scanf("%d",&ops)&&ops){
		switch (ops) {
		case 1:
			scanf("%d %d",&id,&val);
			Insert(id,val);
			break;
		case 2:
			if(!root){
				printf("0\n");
			}else{
				ans=FindMax();
				printf("%d\n",tr[ans].id);
				Delete(tr[ans].val);
			}
			break;
		case 3:
			if(!root){
				printf("0\n");
			}else{
				ans=FindMin();
				printf("%d\n",tr[ans].id);
				Delete(tr[ans].val);
			}
			break;
		}
	}
	return 0;
}
