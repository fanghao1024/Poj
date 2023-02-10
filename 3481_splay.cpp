#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=100010;
int ops,cnt,root,ansMax,ansMin;
struct Tr{
	int fa;
	int son[2];
	int val,id;
}tr[max_n];
void init(){
	cnt=root=0;
	tr[0].son[0]=tr[0].son[1]=0;
}
int newNode(int fa,int id,int val){
	cnt++;
	tr[cnt].id=id;
	tr[cnt].val=val;
	tr[cnt].son[0]=tr[cnt].son[1]=0;
	tr[cnt].fa=fa;
	return cnt;
}
void Rotate(int x){
	int f=tr[x].fa,g=tr[f].fa;
	int c=(tr[f].son[0]==x);
	tr[f].son[!c]=tr[x].son[c];
	tr[tr[x].son[c]].fa=f;
	tr[x].fa=g;
	if(g){
		tr[g].son[tr[g].son[1]==f]=x;
	}
	tr[f].fa=x;
	tr[x].son[c]=f;
}
void Splay(int x,int goal){
	while(tr[x].fa!=goal){
		int f=tr[x].fa,g=tr[f].fa;
		if(g!=goal){
			(tr[g].son[0]==f)^(tr[f].son[0]==x)?Rotate(x):Rotate(f);
		}
		Rotate(x);
	}
	if(goal==0) root=x;
}
void Insert(int id,int val){
	int x;
	for(x=root;tr[x].son[tr[x].val<val];x=tr[x].son[tr[x].val<val]);
	tr[x].son[tr[x].val<val]=newNode(x,id,val);
	Splay(tr[x].son[tr[x].val<val],0);
}

bool Find(int val){
	int x=root;
	while(x){
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

void Findmax(){
	int x=root;
	if(x){
		while(tr[x].son[1]) x=tr[x].son[1];
		Splay(x,0);
	}
}
void Findmin(){
	int x=root;
	if(x){
		while(tr[x].son[0]) x=tr[x].son[0];
		Splay(x,0);
	}
}
bool Split(int val,int& t1,int& t2){
	if(Find(val)){
		t1=tr[root].son[0];
		t2=tr[root].son[1];
		root=t1;
		tr[t1].fa=tr[t2].fa=0;
		return true;
	}
	return false;
}
void Join(int t1,int t2){
	if(t1){
		Findmax();
		tr[root].son[1]=t2;
		tr[t2].fa=root;
	}else{
		root=t2;
	}
}
void Delete(int val){
	int t1=0,t2=0;
	if(Split(val,t1,t2)){
		Join(t1,t2);
	}
}
int main(){
	int id,val;
	init();
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
					Findmax();
					printf("%d\n",tr[root].id);
					Delete(tr[root].val);
				}
				
				break;
			case 3:
				if(!root){
					printf("0\n");
				}else{
					Findmin();
					printf("%d\n",tr[root].id);
					Delete(tr[root].val);
				}
				break;
		}
	}
	return 0;
}
