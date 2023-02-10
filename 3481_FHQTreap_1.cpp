#include<cstdlib>
#include<cstdio>

const int max_n=1000005;

struct Tr{
	int ls,rs;
	int pri,size;
	int id,val;
}tr[max_n];
int cnt,root;
int newNode(int id,int val){
	cnt++;
	tr[cnt].id=id;
	tr[cnt].val=val;
	tr[cnt].ls=tr[cnt].rs=0;
	tr[cnt].pri=rand();
	tr[cnt].size=1;
	return cnt;
}
void Update(int u){
	tr[u].size=tr[tr[u].ls].size+tr[tr[u].rs].size+1;
}
void Split(int u,int val,int& L,int& R){
	if(!u){L=R=0;return;}
	if(tr[u].val<=val){
		L=u;
		Split(tr[u].rs,val,tr[u].rs,R);
	}else{
		R=u;
		Split(tr[u].ls,val,L,tr[u].ls);
	}
	Update(u);
}
int Merge(int L,int R){
	if(!L||!R) return L+R;
	if(tr[L].pri>tr[R].pri){
		tr[L].rs=Merge(tr[L].rs,R);
		Update(L);
		return L;
	}else{
		tr[R].ls=Merge(L,tr[R].ls);
		Update(R);
		return R;
	}
}
void Insert(int id,int val){
	int L,R;
	Split(root,val,L,R);
	root=Merge(Merge(L,newNode(id,val)),R);
}
void Delete(int val){
	int L,R,p;
	Split(root,val,L,R);
	Split(L,val-1,L,p);
	root=Merge(Merge(L,Merge(tr[p].ls,tr[p].rs)),R);
}
int kth(int u,int k){
	if(tr[tr[u].ls].size+1==k) return u;
	if(tr[tr[u].ls].size>=k) return kth(tr[u].ls,k);
	return kth(tr[u].rs,k-tr[tr[u].ls].size-1);
}
int FindMax(){
	return kth(root,tr[root].size);
}
int FindMin(){
	return kth(root,1);
}
int main(){
	int ops,id,val,ans;
	cnt=root=0;
	tr[0].size=tr[0].ls=tr[0].rs=0;
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
		case 3:
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
