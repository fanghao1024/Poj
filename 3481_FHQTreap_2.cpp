#include<cstdio>
#include<cstdlib>

const int max_n=1000005;
struct Tr{
	int ls,rs;
	int pri;
	int id,val;
}tr[max_n];
int cnt,root;

int newNode(int id,int val){
	cnt++;
	tr[cnt].ls=tr[cnt].rs=0;
	tr[cnt].pri=rand();
	tr[cnt].id=id;
	tr[cnt].val=val;
	return cnt;
}
void Split(int x,int val,int& L,int &R){
	if(!x){L=R=0;return ;}
	if(tr[x].val<=val){
		L=x;
		Split(tr[x].rs,val,tr[x].rs,R);
	}else{
		R=x;
		Split(tr[x].ls,val,L,tr[x].ls);
	}
}
int Merge(int L,int R){
	if(!L||!R) return L+R;
	if(tr[L].pri>tr[R].pri){
		tr[L].rs=Merge(tr[L].rs,R);
		return L;
	}else{
		tr[R].ls=Merge(L,tr[R].ls);
		return R;
	}
}
void Insert(int id,int val){
	int L,R;
	Split(root,val,L,R);
	root=Merge(Merge(L,newNode(id,val)),R);
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
void Delete(int val){
	int L,R,p;
	Split(root,val,L,R);
	Split(L,val-1,L,p);
	root=Merge(Merge(L,Merge(tr[p].ls,tr[p].rs)),R);
}
int main(){
	cnt=root=0;
	int ops,id,val,ans;
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
				ans=FindMax();
				printf("%d\n",tr[ans].id);
				Delete(tr[ans].val);
			}
			break;
		default:
			if(!root){
				printf("0\n");
			}else{
				ans=FindMin();
				printf("%d\n",tr[ans].id);
				Delete(tr[ans].val);
			}
			break;
		}
	}
	
	return 0;
}
