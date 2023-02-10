#include<cstdio>
#include<cstdlib>
#include<cmath>

const int max_n=100010;
struct Tr{
	int id,val;
	int l,r;
	int pri;
}tr[max_n];
int N,cnt,root;
int newNode(int id,int val){
	tr[++cnt].val=val;
	tr[cnt].id=id;
	tr[cnt].l=tr[cnt].r=0;
	tr[cnt].pri=rand();
	return cnt;
}
void toRight(int& p){
	int lson=tr[p].l;
	tr[p].l=tr[lson].r;
	tr[lson].r=p;
	p=lson;
}
void toLeft(int& p){
	int rson=tr[p].r;
	tr[p].r=tr[rson].l;
	tr[rson].l=p;
	p=rson;
}
void Insert(int& p,int id,int val){
	if(!p){
		p=newNode(id,val);
		return ;
	}
	if(tr[p].val>val){
		Insert(tr[p].l,id,val);
		if(tr[tr[p].l].pri>tr[p].pri) toRight(p);
	}else{
		Insert(tr[p].r,id,val);
		if(tr[tr[p].r].pri>tr[p].pri) toLeft(p);
	}
}
int getPre(int p,int val){
	int res=0;
	while(p){
		if(tr[p].val<val){
			res=p;
			p=tr[p].r;
		}else{
			p=tr[p].l;
		}
	}
	return res;
}
int getNext(int p,int val){
	int res=0;
	while(p){
		if(tr[p].val>val){
			res=p;
			p=tr[p].l;
		}else{
			p=tr[p].r;
		}
	}
	return res;
}
int solve(int p,int val){
	int pre=getPre(p,val);
	int nxt=getNext(p,val);
	if(!pre||!nxt) return tr[pre+nxt].id;
	if(abs(tr[pre].val-val)<abs(tr[nxt].val-val)){
		return tr[pre].id;
	}else{
		if(abs(tr[pre].val-val)>abs(tr[nxt].val-val)){
			return tr[nxt].id;
		}else{
			if(tr[pre].val<val) return tr[pre].id;
			else return tr[nxt].id;
		}
	}
}
int main(){
	int id,val;
	while(scanf("%d",&N)&&N){
		cnt=root=0;
		Insert(root,1,1000000000);
		for(int i=2;i<=N+1;i++){
			scanf("%d %d",&id,&val);
			printf("%d %d\n",id,solve(root,val));
			Insert(root,id,val);
		}
	}
	return 0;
}
