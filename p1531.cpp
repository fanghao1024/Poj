#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=2e5+10;

int num[max_n],tree[max_n];
int N,M;
char Q[10];
int lowbit(int x){return x&(-x);}
void update(int pos,int x){
	num[pos]=x;
	while(pos<=N){
		tree[pos]=num[pos];
		for(int i=1;i<lowbit(pos);i<<=1)
			tree[pos]=max(tree[pos],tree[pos-i]);
		pos+=lowbit(pos);
	}
}
void add(int pos,int x){//修改学生的成绩
	num[pos]=x;
	while(pos<=N){
		tree[pos]=num[pos];
		int t=lowbit(pos);
		for(int j=1;j<t;j<<=1){
			tree[pos]=max(tree[pos],tree[pos-j]);
		}
		pos+=lowbit(pos);
	}
}
int query(int L,int R){
	if(L==R) return num[L];
	if(R-L+1>lowbit(R)) return max(tree[R],query(L,R-lowbit(R)));
	else return max(num[R],query(L,R-1));
}
int query1(int L,int R){
	int ans=0;
	while(L<=R){
		ans=max(ans,num[R]);
		R--;
		while(R-L>=lowbit(R)){
			ans=max(ans,tree[R]);
			R-=lowbit(R);
		}
	}
	return ans;
}
int getmax(int l,int r){//找区间最大值
	int res=0;
	if(!r) return res;
	int i=r;
	while(i>=l){
		int j=i-lowbit(i)+1;
		if(j>l){
			res=max(res,tree[i]);
			i=j-1;
		}
		else{
			res=max(res,num[i]);
			--i;
		}
	}
	return res;
}
int main(){
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++) scanf("%d",&num[i]);
	memset(tree,0,sizeof(tree));
	for(int i=1;i<=N;i++) update(i,num[i]);
	int x,y;
	while(M--){
		scanf("%s %d %d",Q,&x,&y);
		if(Q[0]=='Q'){
			printf("%d\n",query(x,y));
		}else{
			if(num[x]<y){
				
				update(x,y);
			//	add(x,y);
			}
		}
	}
	return 0;
}
