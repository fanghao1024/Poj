#include<cstdio>
#include<cstdlib>

const int max_n=1000005;

struct Tr{
	int ls,rs;
	int pri;
	int id,val;
}tr[max_n];
int cnt,root;
void init(){
	cnt=root=0;
}
int newNode(int id,int val){
	cnt++;
	tr[cnt].ls=tr[cnt].rs=0;
	tr[cnt].pri=rand();
	tr[cnt].id=id;
	tr[cnt].val=val;
	return cnt;
}
void Toleft(int& p){
	int rson=tr[p].rs;
	tr[p].rs=tr[rson].ls;
	tr[rson].ls=p;
	p=rson;
}
void Toright(int& p){
	int lson=tr[p].ls;
	tr[p].ls=tr[lson].rs;
	tr[lson].rs=p;
	p=lson;
}
void Insert(int& u,int id,int val){
	if(!u){
		u=newNode(id,val);
		return ;
	}
	if(tr[u].val<val){
		Insert(tr[u].rs,id,val);
		if(tr[tr[u].rs].pri>tr[u].pri) Toleft(u);
	}else{
		Insert(tr[u].ls,id,val);
		if(tr[tr[u].ls].pri>tr[u].pri) Toright(u);
	}
}
int FindMax(){
	int x=root;
	while(tr[x].rs) x=tr[x].rs;
	return x;
}
int FindMin(){
	int x=root;
	while(tr[x].ls) x=tr[x].ls;
	return x;
}
void Delete(int& u,int val){
	if(!u) return;
	if(tr[u].val==val){
		if(!tr[u].ls||!tr[u].rs){
			u=tr[u].ls+tr[u].rs;
			return ;
		}
		if(tr[tr[u].ls].pri>tr[tr[u].rs].pri){
			Toright(u);
			Delete(tr[u].rs,val);
		}else{
			Toleft(u);
			Delete(tr[u].ls,val);
		}
	}else{
		if(tr[u].val<val){
			Delete(tr[u].rs,val);
		}else{
			Delete(tr[u].ls,val);
		}
	}
	
}
int main(){
	int ops,id,val,ans;
	init();
	while(scanf("%d",&ops)&&ops){
		switch (ops) {
		case 1:
			scanf("%d %d",&id,&val);
			Insert(root,id,val);
			break;
		case 2:
			if(!root){
				printf("0\n");
			}else{
				ans=FindMax();
				printf("%d\n",tr[ans].id);
				Delete(root,tr[ans].val);
			}
			break;
		default:
			if(!root){
				printf("0\n");
			}else{
				ans=FindMin();
				printf("%d\n",tr[ans].id);
				Delete(root,tr[ans].val);
			}
			break;
		}
	}
	return 0;
	
}
