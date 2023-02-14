#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

const int max_n=2005;
int N,cnts;
int a[max_n],b[max_n];
int root[max_n],num[max_n];
struct Node{
	int l,r;
	int sz,key,dis;
}node[max_n];
int newNode(int val){
	cnts++;
	node[cnts].l=node[cnts].r=0;
	node[cnts].sz=1;
	node[cnts].key=val;
	node[cnts].dis=0;
	return cnts;
}
int merge(int x,int y){
	if(!x||!y) return x+y;
	if(node[x].key<node[y].key) swap(x,y);
	node[x].r=merge(node[x].r,y);
	if(node[node[x].l].dis<node[node[x].r].dis) swap(node[x].l,node[x].r);
	node[x].dis=node[node[x].r].dis+1;
	node[x].sz=node[node[x].l].sz+node[node[x].r].sz+1;
	return x;
}
void Pop(int& x){
	x=merge(node[x].l,node[x].r);
}
int Top(int x){return node[x].key;}
int solve(int a[]){
	int cnt=0;
	int ans=0;
	cnts=0;
	for(int i=0;i<N;i++){
		root[++cnt]=newNode(a[i]);
		num[cnt]=1;
		while(cnt>1&&Top(root[cnt])<Top(root[cnt-1])){
			cnt--;
			root[cnt]=merge(root[cnt],root[cnt+1]);
			num[cnt]+=num[cnt+1];
			if(node[root[cnt]].sz*2>num[cnt]+1) Pop(root[cnt]);
		}
	}
	int k=0;
	for(int i=1;i<=cnt;i++){
		for(int j=0;j<num[i];j++){
			ans+=abs(a[k++]-node[root[i]].key);
		}
	}
	return ans;
}
int main(){
	while(scanf("%d",&N)!=EOF){
		for(int i=0;i<N;i++){
			scanf("%d",&a[i]);
			b[N-1-i]=a[i];
		}
		printf("%d\n",min(solve(a),solve(b)));
	}
	
	return 0;
}
