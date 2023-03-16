#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;

const int max_n=5e4+10;
const int inf=0x3f3f3f3f;
int N;
struct Tree{
	char s[300];
	int pri;
	int l,r,fa;
}tr[max_n];
bool cmp(const Tree& a,const Tree& b){
	return strcmp(a.s,b.s)<0;
}
void build_tree(){
	for(int i=1;i<=N;i++){
		int pos=i-1;
		while(tr[pos].pri<tr[i].pri) pos=tr[pos].fa;
		tr[i].l=tr[pos].r;
		tr[tr[pos].r].fa=i;
		tr[pos].r=i;
		tr[i].fa=pos;
	}
}
void build_tree1(){
	stack<int> si;
	si.push(0);
	for(int i=1;i<=N;i++){
		int pos=si.top();
		while(tr[pos].pri<tr[i].pri){
			pos=tr[pos].fa;
			si.pop();
		}
		tr[i].l=tr[pos].r;
		tr[tr[i].l].fa=i;
		tr[pos].r=i;
		tr[i].fa=pos;
		si.push(i);
	}
}

void inorder(int u){
	if(!u) return ;
	printf("(");
	inorder(tr[u].l);
	printf("%s/%d",tr[u].s,tr[u].pri);
	inorder(tr[u].r);
	printf(")");
}
int main(){
	while(scanf("%d",&N)&&N){
		for(int i=1;i<=N;i++){
			tr[i].l=tr[i].r=tr[i].fa=0;
			scanf(" %[^/]/%d",tr[i].s,&tr[i].pri);
		}
		tr[0].l=tr[0].r=tr[0].fa=0;
		tr[0].pri=inf;
		sort(tr+1,tr+1+N,cmp);
		build_tree1();
		inorder(tr[0].r);printf("\n");
	}
	return 0;
}
