#include<cstdio>
#include<cstdlib>
#include<ctime>

const int inf=0;
const int max_n=100010;
int N,cnt,root;
struct Tr{
	int l,r;
	int pri;
	int num; //该值的个数
	int val;
	int siz;//子树个数，包含自身
}tr[max_n];
int newNode(int val){
	tr[++cnt].val=val;
	tr[cnt].num=1;
	tr[cnt].siz=1;
	tr[cnt].l=tr[cnt].r=0;
	tr[cnt].pri=rand();
	return cnt;
}
void push_up(int p){
	tr[p].siz=tr[tr[p].l].siz+tr[tr[p].r].siz+tr[p].num;
}
void toright(int& p){
	int lson=tr[p].l;
	tr[p].l=tr[lson].r;
	tr[lson].r=p;
	push_up(p);
	p=lson;
	push_up(p);
}
void toleft(int& p){
	int rson=tr[p].r;
	tr[p].r=tr[rson].l;
	tr[rson].l=p;
	push_up(p);
	p=rson;
	push_up(p);
}
void Insert(int& p,int val){
	if(!p){
		p=newNode(val);
		return ;
	}
	tr[p].siz++;
	if(tr[p].val==val){
		tr[p].num++;
	}else{
		if(tr[p].val>val){
			Insert(tr[p].l,val);
			if(tr[tr[p].l].pri>tr[p].pri) toright(p);
		}else{
			Insert(tr[p].r,val);
			if(tr[tr[p].r].pri>tr[p].pri) toleft(p);
		}
	}
}
void Delete(int& p,int val){
	if(!p) return ;
	tr[p].siz--;
	if(tr[p].val==val){
		if(tr[p].num>1){
			tr[p].num--;
			return ;
		}
		if(!tr[p].l||!tr[p].r){
			p=tr[p].l+tr[p].r;
		}else{
			if(tr[tr[p].l].pri>tr[tr[p].r].pri){
				toright(p);
				Delete(tr[p].r,val);
			}else{
				toleft(p);
				Delete(tr[p].l,val);
			}
		}
		
	}else{
		if(tr[p].val>val){
			Delete(tr[p].l,val);
		}else{
			Delete(tr[p].r,val);
		}
	}
}
int getPre(int p,int val){
	int res=0;
	while(p){
		if(tr[p].val>=val){
			p=tr[p].l;
		}else{
			res=tr[p].val;
			p=tr[p].r;
		}
	}
	return res;
}
int getAfter(int p,int val){
	int res=0;
	while(p){
		if(tr[p].val>val){
			res=tr[p].val;
			p=tr[p].l;
		}else{
			p=tr[p].r;
		}
	}
	return res;
}
int printOrder(int p,int val){
	if(!p) return 0;
	if(tr[p].val==val) return tr[tr[p].l].siz+1;
	if(tr[p].val>val){
		return printOrder(tr[p].l,val);
	}
	else{
		return tr[tr[p].l].siz+tr[p].num+printOrder(tr[p].r,val);
	}
	
}
int getValByRank(int p,int val){
	if(!p) return 0;
	if(tr[tr[p].l].siz>=val) return getValByRank(tr[p].l,val);
	if(tr[p].num+tr[tr[p].l].siz>=val) return tr[p].val;
	return getValByRank(tr[p].r,val-tr[p].num-tr[tr[p].l].siz);
}
int main(){
	scanf("%d",&N);
	int op,x,pos;
	cnt=root=0;
	//srand(time(0));
	while(N--){
		scanf("%d %d",&op,&x);
		switch(op){
			case 1:
				Insert(root,x);
				break;
			case 2:
				Delete(root,x);
				break;
			case 3:
				printf("%d\n",printOrder(root,x));
				break;
			case 4:
				printf("%d\n",getValByRank(root,x));
				break;
			case 5:
				printf("%d\n",getPre(root,x));
				break;
			case 6:
				printf("%d\n",getAfter(root,x));
				break;
		}
	}
	return 0;
}
