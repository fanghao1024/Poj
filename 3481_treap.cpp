#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;

const int max_n=100005;
struct Node{
	int l,r;
	int pri;
	int val,num;
}node[max_n];
int cnt,root,ansMax,ansMin;
int newNode(int x,int y){
	node[++cnt].val=y;
	node[cnt].num=x;
	node[cnt].l=node[cnt].r=0;
	node[cnt].pri=rand();
	return cnt;
}
void toright(int& p){
	int lson=node[p].l;
	node[p].l=node[lson].r;
	node[lson].r=p;
	p=lson;
}
void toleft(int& p){
	int rson=node[p].r;
	node[p].r=node[rson].l;
	node[rson].l=p;
	p=rson;
}
void insert(int& p,int x,int y){
	if(!p){
		p=newNode(x,y);
		return ;
	}
	if(node[p].val>=y){
		insert(node[p].l,x,y);
		if(node[node[p].l].pri>node[p].pri)	toright(p);
	}else{

			insert(node[p].r,x,y);
			if(node[node[p].r].pri>node[p].pri)	toleft(p);
		
	}
}
void printMax(int p){
	while(node[p].r){
		p=node[p].r;
	}
	ansMax=node[p].val;
	printf("%d\n",node[p].num);
	
}
void printMin(int p){
	while(node[p].l){
		p=node[p].l;
	}
	ansMin=node[p].val;
	printf("%d\n",node[p].num);
	
}
void Delete(int& p,int val){
	if(!p) return ;
	if(val==node[p].val){
		if(!node[p].l||!node[p].r){
			p=node[p].l+node[p].r;
		}else{
			if(node[node[p].l].pri>node[node[p].r].pri){
				toright(p);
				Delete(node[p].r,val);
			}else{
				toleft(p);
				Delete(node[p].l,val);
			}
		}
	
	}else{
		if(val>node[p].val) {Delete(node[p].r,val);}
		else{Delete(node[p].l,val);}
	}
	
}
int main(){
	int op,x,y;
	srand(time(0));
	cnt=0;
	root=0;
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
