#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int max_n=2005;
int N,cnts;
int a[max_n],b[max_n],root[max_n],num[max_n];
struct Tr{
	int l,r;
	int sz,dep,key;
}tr[max_n];
int newNode(int val){
	tr[++cnts].key=val;
	tr[cnts].l=tr[cnts].r=0;
	tr[cnts].dep=0;
	tr[cnts].sz=1;
	return cnts;
}
int Merge(int x,int y){
	if(!x||!y) return x+y;
	if(tr[x].key<tr[y].key) swap(x,y);
	tr[x].r=Merge(tr[x].r,y);
	if(tr[tr[x].l].dep<tr[tr[x].r].dep) swap(tr[x].l,tr[x].r);
	tr[x].dep=tr[tr[x].r].dep+1;
	tr[x].sz=tr[tr[x].l].sz+tr[tr[x].r].sz+1;
	return x;
}
int Top(int x){return tr[x].key;}
void Pop(int& x){x=Merge(tr[x].l,tr[x].r);}
int solve(int a[]){
	int cnt=0;
	cnts=0;
	for(int i=0;i<N;i++){
		root[++cnt]=newNode(a[i]);
		num[cnt]=1;
		while(cnt>1&&Top(root[cnt])<Top(root[cnt-1])){
			cnt--;
			root[cnt]=Merge(root[cnt],root[cnt+1]);
			num[cnt]+=num[cnt+1];
			if(tr[root[cnt]].sz*2>num[cnt]+1) Pop(root[cnt]);
		}
	}
	int ans=0;
	int k=0;
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=num[i];j++){
			ans+=abs(a[k++]-tr[root[i]].key);
		}
	}
	return ans;
}
int main(){
	while(scanf("%d",&N)!=EOF){
		for(int i=0;i<N;i++) scanf("%d",&a[i]),b[N-1-i]=a[i];
		printf("%d\n",min(solve(a),solve(b)));
	}
	return 0;
}
