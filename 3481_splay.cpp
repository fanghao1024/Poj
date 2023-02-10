#include<cstdio>

const int man_n=1000005;
int ops,cnt,root;
struct Tr{
	int son[2];
	int fa;
	int id,val;
}tr[man_n];
void init(){
	cnt=root=0;
	tr[0].son[0]=tr[0].son[1]=0;
}
int newNode(int father,int id,int val){
	cnt++;
	tr[cnt].fa=father;
	tr[cnt].son[0]=tr[cnt].son[1]=0;
	tr[cnt].id=id;
	tr[cnt].val=val;
	return cnt;
}
void Rotate(int x){
	int f=tr[x].fa,g=tr[f].fa;
	int c=(tr[f].son[0]==x);
	tr[f].son[!c]=tr[x].son[c];
	tr[tr[x].son[c]].fa=f;
	tr[x].fa=g;
	if(g) tr[g].son[tr[g].son[1]==f]=x;
	tr[x].son[c]=f;
	tr[f].fa=x;
}
void Splay(int x,int goal){
	while(tr[x].fa!=goal){
		int f=tr[x].fa,g=tr[f].fa;
		if(g!=goal) (tr[g].son[0]==f)^(tr[f].son[0]==x)?Rotate(x):Rotate(f);
		Rotate(x);
	}
	if(!goal) root=x;
}
void Insert(int id,int val){
	int x;
	for(x=root;tr[x].son[tr[x].val<val];x=tr[x].son[tr[x].val<val]);
	tr[x].son[tr[x].val<val]=newNode(x,id,val);
	Splay(tr[x].son[tr[x].val<val],0);
}
void FindMax(){
	int x=root;
	if(x){
		while(tr[x].son[1]) x=tr[x].son[1];
		Splay(x,0);
	}
}
void FindMin(){
	int x=root;
	if(x){
		while(tr[x].son[0]) x=tr[x].son[0];
		Splay(x,0);
	}
}
bool Find(int val){
	int x=root;
	while(1){
		if(tr[x].val==val){
			Splay(x,0);
			return true;
		}
		if(tr[x].son[tr[x].val<val]){
			x=tr[x].son[tr[x].val<val];
		}else{
			Splay(x,0);
			return false;
		}
	}
}
bool Split(int val,int& t1,int& t2){
	if(Find(val)){
		t1=tr[root].son[0];
		t2=tr[root].son[1];
		tr[t1].fa=tr[t2].fa=0;
		root=t1;
		return true;
	}
	return false;
}
void Join(int t1,int t2){
	if(t1){
		FindMax();
		tr[root].son[1]=t2;
		tr[t2].fa=root;
	}else{
		root=t2;
		if(!root) init();
	}
}
void Delete(int val){
	int t1=0,t2=0;
	if(Split(val,t1,t2)){
		Join(t1,t2);
	}
}
int main(){
	init();
	int id,val;
	while(scanf("%d",&ops)&&ops){
		switch(ops){
			case 1:
				scanf("%d %d",&id,&val);
				Insert(id,val);
				break;
			case 2:
				if(!root){
					printf("0\n");
				}else{
					FindMax();
					printf("%d\n",tr[root].id);
					Delete(tr[root].val);
				}
				break;
			case 3:
				if(!root){
					printf("0\n");
				}else{
					FindMin();
					printf("%d\n",tr[root].id);
					Delete(tr[root].val);
				}
				break;
		}
	}
	return 0;
}
