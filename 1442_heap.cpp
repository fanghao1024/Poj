#include<cstdio>
#include<cstdlib>
#include<ctime>

const int max_n=30010;
struct Tr{
	int l,r;
	int val,pri;
	int num,size;
}tr[max_n];
int Add[max_n];
int Get[max_n];
int M,N,cnt,root;

int newNode(int val){
	tr[++cnt].val=val;
	tr[cnt].l=tr[cnt].r=0;
	tr[cnt].num=tr[cnt].size=1;
	tr[cnt].pri=rand();
	return cnt;
}
void push_up(int p){
	tr[p].size=tr[tr[p].l].size+tr[tr[p].r].size+tr[p].num;
}
void toRight(int& p){
	int lson=tr[p].l;
	tr[p].l=tr[lson].r;
	tr[lson].r=p;
	push_up(p);
	p=lson;
	push_up(p);
}
void toLeft(int& p){
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
	tr[p].size++;
	if(tr[p].val==val){
		tr[p].num++;
		return ;
	}
	if(tr[p].val<val){
		Insert(tr[p].r,val);
		if(tr[tr[p].r].pri>tr[p].pri){
			toLeft(p);
		}
	}else{
		Insert(tr[p].l,val);
		if(tr[tr[p].l].pri>tr[p].pri){
			toRight(p);
		}
	}
}
int getValByRank(int p,int k){
	if(!p) return 0;
	if(tr[tr[p].l].size>=k) return getValByRank(tr[p].l,k);
	if(tr[tr[p].l].size+tr[p].num>=k) return tr[p].val;
	return getValByRank(tr[p].r,k-tr[tr[p].l].size-tr[p].num);
}
int main(){
	scanf("%d %d",&M,&N);
	for(int i=1;i<=M;i++) scanf("%d",Add+i);
	for(int i=1;i<=N;i++) scanf("%d",Get+i);
	cnt=root=0;
	int j=1;
	int k=1;
	for(int i=1;i<=M;i++){
		if(i<=Get[j]){
			Insert(root,Add[i]);
		}
		while(j<=N&&Get[j]==i){
			printf("%d\n",getValByRank(root,k));
			j++;
			k++;
		}
	}
	return 0;
}
