#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;

const int max_n=100010;
//typedef vector<int>ve; 
//vector<ve> vv(100005);
vector<vector<int> > vv(max_n);

int tree[max_n];
int L[max_n],R[max_n];
int N,M;
int cnt;

int lowbit(int x){
	return x&(-x);
}
void update(int x,int d){
	while(x<=N){
		tree[x]+=d;
		x+=lowbit(x);
	}
}
int sum(int x){
	int res=0;
	while(x>0){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}

void dfs(int node){
	cnt++;
	//printf("~~~%d %d\n",cnt,node);
	L[node]=cnt;
	//printf("===%d\n",L[node]);
	//printf("sieze:%d\n",vv[node].size());
	for(int i=0;i<vv[node].size();i++){
		if(L[vv[node][i]]==-1){
			dfs(vv[node][i]);
		}	
	}
	R[node]=cnt;
}
int main(){
	scanf("%d",&N);
	for(int i=1;i<N;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		vv[u].push_back(v);
		vv[v].push_back(u);
	}
	memset(L,-1,sizeof(L));
	memset(R,-1,sizeof(R));
	cnt=0;
	dfs(1);

	for(int i=1;i<=N;i++){
		update(i,1);
	}
	char ch;
	int x;
	scanf("%d",&M);
	while(M--){
		scanf(" %c %d",&ch,&x);
		switch (ch) {
		case 'C':
			
			if(sum(L[x])-sum(L[x]-1)==1){
				update(L[x],-1);
			}else{
				update(L[x],1);
			}
			break;
		case 'Q':
			printf("%d\n",sum(R[x])-sum(L[x]-1));
			break;
		}
	}
	
	return 0;
}
