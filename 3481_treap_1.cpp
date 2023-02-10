#include<cstdio>
#include<cstdlib>
#include<ctime>

const int max_n=100005;
int cnt,root,ansMax,ansMin;
struct Tr{
	int l,r;
	int num,val;
	int pri;
}tr[max_n];
int newTr(int x,int y){
	tr[++cnt].num=x;
	tr[cnt].val=y;
	tr[cnt].l=tr[cnt].r=0;
	tr[cnt].pri=rand();
	return cnt;
}
void toright(int& p){
	int lson=tr[p].l;
	tr[p].l=tr[lson].r;
	tr[lson].r=p;
	p=lson;
}
void toleft(int& p){
	int rson=tr[p].r;
	tr[p].r=tr[rson].l;
	tr[rson].l=p;
	p=rson;
}
void insert(int& p,int x,int y){
	if(!p){
		p=newTr(x,y);
		return ;
	}
	if(y<tr[p].val){
		insert(tr[p].l,x,y);
		if(tr[tr[p].l].pri>tr[p].pri) toright(p);
	}else{
		insert(tr[p].r,x,y);
		if(tr[tr[p].r].pri>tr[p].pri) toleft(p);
	}
}
void printMax(int p){
	while(tr[p].r) p=tr[p].r;
	printf("%d\n",tr[p].num);
	ansMax=tr[p].val;
}
void printMin(int p){
	while(tr[p].l) p=tr[p].l;
	printf("%d\n",tr[p].num);
	ansMin=tr[p].val;
}
void Delete(int& p,int val){
	if(!p) return ;
	if(tr[p].val==val){
		if(!tr[p].l||!tr[p].r){
			p=tr[p].l+tr[p].r;
		}else{
			if(tr[tr[p].l].pri>=tr[tr[p].r].pri){
				toright(p);
				Delete(tr[p].r,val);
			}else{
				toleft(p);
				Delete(tr[p].l,val);
			}
		}
	}else{
		if(val>tr[p].val){
			Delete(tr[p].r,val);
		}else{
			Delete(tr[p].l,val);
		}
	}
}
int main(){
	int op,x,y;
	cnt=root=0;
	while(scanf("%d",&op)&&op){
		switch (op) {
		case 1:
			scanf("%d %d",&x,&y);
			insert(root,x,y);
			break;
		case 2:
			if(!root){
				printf("0\n");
			}else{
				printMax(root);
				Delete(root,ansMax);
			}
			break;
		case 3:
			if(!root){
				printf("0\n");
			}else{
				printMin(root);
				Delete(root,ansMin);
			}
			break;
		}
		
	}
	return 0;
}
