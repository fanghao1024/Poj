#include<cstdio>

const int max_n=1000005;
int cnt,root;
struct Tr{
	int son[2];
	int id,val;
	int fa;
}tr[max_n];
void Init(){
	cnt=root=0;
	tr[0].son[0]=tr[0].son[1]=0;
}

int newNode(int father,int id,int val){
	cnt++;
	tr[cnt].fa=father;
	tr[cnt].id=id;
	tr[cnt].val=val;
	tr[cnt].son[0]=tr[cnt].son[1]=0;
	return cnt;
}
void Rotate(int x){
	int f=tr[x].fa,g=tr[f].fa;
	int c=tr[f].son[0]==x;
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
		if(g!=goal) (tr[f].son[0]==x)^(tr[g].son[0]==f)?Rotate(x):Rotate(f);
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
	while(tr[x].son[1]) x=tr[x].son[1];
	Splay(x,0);
}
void FindMin(){
	int x=root;
	while(tr[x].son[0]) x=tr[x].son[0];
	Splay(x,0);
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
bool Split(int p,int val,int& L,int& R){
	if(Find(val)){
		L=tr[root].son[0];
		R=tr[root].son[1];
		root=L;
		tr[L].fa=tr[R].fa=0;
		return true;
	}
}
void Join(int t1,int t2){
	if(t1){
		FindMax();
		tr[root].son[1]=t2;
		tr[t2].fa=root;
	}else{
		root=t2;
		if(!root) Init();
	}
}
void Delete(int val){
	int t1=0,t2=0;
	if(Split(root,val,t1,t2)){
		Join(t1,t2);
	}
}
int main(){
	int ops,id,val;
	Init();
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
				FindMax();
				printf("%d\n",tr[root].id);
				Delete(tr[root].val);
			}
			break;
		default:
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
