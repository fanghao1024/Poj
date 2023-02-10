#include<cstdio>
#include<cstdlib>

const int max_n=1000005;
struct Tr{
	int son[2];
	int id,val;
	int pri;
}tr[max_n];
int ops,cnt,root;
void init(){
	cnt=root=0;
}
int newNode(int id,int val){
	tr[++cnt].id=id;
	tr[cnt].val=val;
	tr[cnt].son[0]=tr[cnt].son[1]=0;
	tr[cnt].pri=rand();
	return cnt;
}
void Rotate(int& p,int d){
	int k;
	if(d==1){
		k=tr[p].son[0];
		tr[p].son[0]=tr[k].son[1];
		tr[k].son[1]=p;
		
	}else{
		k=tr[p].son[1];
		tr[p].son[1]=tr[k].son[0];
		tr[k].son[0]=p;
	}
	p=k;
	
}
void Delete(int& x,int val){
	if(!x) return ;
	if(tr[x].val==val){
		if(!tr[x].son[0]||!tr[x].son[1]) x=tr[x].son[0]+tr[x].son[1];
		else{
			if(tr[tr[x].son[0]].pri>tr[tr[x].son[1]].pri){
				Rotate(x,1);
				Delete(tr[x].son[1],val);
			}else{
				Rotate(x,0);
				Delete(tr[x].son[0],val);
			}
		}
	}else{
		if(tr[x].val<val){
			Delete(tr[x].son[1],val);
		}else{
			Delete(tr[x].son[0],val);
		}
	}
}
void FindMax(){
	int x=root;
	if(x){
		while(tr[x].son[1]) x=tr[x].son[1];
		printf("%d\n",tr[x].id);
		Delete(root,tr[x].val);
	}else{
		printf("0\n");
	}
}
void FindMin(){
	int x=root;
	if(x){
		while(tr[x].son[0]) x=tr[x].son[0];
		printf("%d\n",tr[x].id);
		Delete(root,tr[x].val);
	}else{
		printf("0\n");
	}
}
void Insert(int& p,int id,int val){
	if(!p){
		p=newNode(id,val);
		return ;
	}
	if(tr[p].val<val){
		Insert(tr[p].son[1],id,val);
		if(tr[tr[p].son[1]].pri>tr[p].pri) Rotate(p,0);
	}else{
		Insert(tr[p].son[0],id,val);
		if(tr[tr[p].son[0]].pri>tr[p].pri) Rotate(p,1);
	}
}
int main(){
	int id,val;
	while(scanf("%d",&ops)&&ops){
		switch (ops) {
		case 1:
			scanf("%d %d",&id,&val);
			Insert(root,id,val);
			break;
		case 2:
			FindMax();
			break;
		case 3:
			FindMin();
			break;
		}
	}
	return 0;
}
