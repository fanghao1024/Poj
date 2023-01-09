#include<stdio.h>
#include<algorithm>
using namespace std;

struct Edge{
	int start,end;
	int cost;
}edge[50010];

int par[20010];
int ranks[20010];

void init(int n){
	for(int i=0;i<n;i++){
		par[i]=i;
		ranks[i]=1;
	}
}
int find(int index){
	if(par[index]==index){
		return index;
	}
	par[index]=find(par[index]);
	return par[index];
}
void unite(int i,int j){
	int x=find(i);
	int y=find(j);
	if(x==y) return;
	if(ranks[x]>ranks[y]){
		par[y]=x;
	}else{
		par[x]=y;
		if(ranks[x]==ranks[y]){
			ranks[y]++;
		}
	}
}
bool same(int i,int j){
	return find(i)==find(j);
}
bool cmp(const Edge& a,const Edge& b){
	return a.cost<b.cost;
}

int main(){
	int case_num;
	scanf("%d\n",&case_num);
	while(case_num--){
		int N,M,R;
		scanf("%d %d %d",&N,&M,&R);
		int x,y,d;
		for(int i=0;i<R;i++){
			scanf("%d %d %d",&x,&y,&d);
			y=y+N;
			edge[i].start=x;
			edge[i].end=y;
			edge[i].cost=-d;
		}
		sort(edge,edge+R,cmp);
		init(N+M);
		int ans=0;
		for(int i=0;i<R;i++){
			if(!same(edge[i].start,edge[i].end)){
				ans+=edge[i].cost;
				unite(edge[i].start,edge[i].end);
			}
		}
		printf("%d\n",10000*(N+M)+ans);
	}
	return 0;
}
