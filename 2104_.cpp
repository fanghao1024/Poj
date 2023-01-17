#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

const int B=1000;
const int max_n=100010;
const int max_m=5010;
int A[max_n];
int num[max_n];
int I[max_m],J[max_m],K[max_m];

vector<int> tree[max_n*4];
int ls(int p){return p<<1;}
int rs(int p){return p<<1|1;}

void init(int p,int l,int r){
	if(l==r){
		tree[p].push_back(A[l]);
	}else{
		int mid=(l+r)>>1;
		init(ls(p),l,mid);
		init(rs(p),mid+1,r);
		tree[p].resize(r-l+1);
		merge(tree[ls(p)].begin(),tree[ls(p)].end(),tree[rs(p)].begin(),tree[rs(p)].end(),tree[p].begin());
	}
}

int query(int L,int R,int x,int p,int pl,int pr){
	if(L>pr||R<pl) return 0;
	if(L<=pl&&R>=pr) return upper_bound(tree[p].begin(),tree[p].end(),x)-tree[p].begin();
	int mid=(pl+pr)>>1;
	int count=0;
	count+=query(L,R,x,ls(p),pl,mid);
	count+=query(L,R,x,rs(p),mid+1,pr);
	return count;
}
int N,M;
int main(){
	scanf("%d %d",&N,&M);
	for(int i=1;i<=N;i++) scanf("%d",&A[i]);
	for(int i=0;i<M;i++) scanf("%d %d %d",&I[i],&J[i],&K[i]);
	for(int i=1;i<=N;i++){
		num[i]=A[i];
	}
	sort(num+1,num+N+1);
	init(1,1,N);
	for(int i=0;i<M;i++){
		int l=I[i],r=J[i],k=K[i];
		
		int lb=0,ub=N;
		while(ub>lb+1){
			int mid=(lb+ub)>>1;
			int x=num[mid];
			if(query(l,r,x,1,1,N)>=k){
				ub=mid;
			}else{
				lb=mid;
			}
		}
		printf("%d\n",num[ub]);
	}
	
	return 0;
}
