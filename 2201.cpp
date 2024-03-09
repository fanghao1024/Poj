#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;

const int max_n=5e4+10;
const int inf=0x3f3f3f3f;

struct Tree{
	int l,r,fa;
	int k,a;
	int id;
}tr[max_n];
bool cmp1(const Tree& a,const Tree& b){
	return a.k<b.k;
}
bool cmp2(const Tree& a,const Tree& b){
	return a.id<b.id;
}
int N;
stack<int> si;
void build_tree(int n){
	while(!si.empty()) si.pop();
	si.push(0);
	for(int i=1;i<=n;i++){
		int pos=si.top();
		while(tr[pos].a>tr[i].a){
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
int main(){
	while(scanf("%d",&N)!=EOF){
		for(int i=1;i<=N;i++){
			tr[i].l=tr[i].r=tr[i].fa=0;
			tr[i].id=i;
			scanf("%d %d",&tr[i].k,&tr[i].a);
		}
		tr[0].l=tr[0].r=tr[0].fa=0;
		tr[0].a=-inf;
		sort(tr+1,tr+1+N,cmp1);
		build_tree(N);
		for(int i=1;i<=N;i++){
			if(tr[i].fa) tr[i].fa=tr[tr[i].fa].id;
			if(tr[i].l) tr[i].l=tr[tr[i].l].id;
			if(tr[i].r) tr[i].r=tr[tr[i].r].id;
		}
		sort(tr+1,tr+1+N,cmp2);
		printf("YES\n");
		for(int i=1;i<=N;i++){
			printf("%d %d %d\n",tr[i].fa,tr[i].l,tr[i].r);
		}
	}
	return 0;
}
