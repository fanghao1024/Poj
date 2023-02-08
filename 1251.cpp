#include<iostream>
#include<algorithm>
using namespace std;

const int max_n=30;
const int max_e=100;
int cnt;
struct Edge{
	int s,e;
	int cost;	
}edge[max_e];
bool cmp(const Edge& a,const Edge& b){
	return a.cost<b.cost;
}
int par[max_n];
int ranks[max_n];
int N;
void build(int n){
	for(int i=1;i<=n;i++){
		par[i]=i;
		ranks[i]=1;
	}
}
int find(int x){
	if(x!=par[x]){
		par[x]=find(par[x]);
	}
	return par[x];
}
void unite(int x,int y){
	int a=find(x);
	int b=find(y);
	if(a!=b){
		if(ranks[a]>ranks[b]){
			par[b]=a;
		}else{
			par[a]=b;
			if(ranks[a]==ranks[b]){
				ranks[b]++;
			}
		}
	}
}
bool same(int x,int y){
	return find(x)==find(y);
}
int main(){
	while(cin>>N){
		if(!N) break;
		cnt=0;
		char ch;
		for(int i=1;i<N;i++){
			int k;
			cin>>ch>>k;
			
			int c;
			for(int j=0;j<k;j++){
				cin>>ch>>c;
				edge[cnt].e=ch-'A'+1;
				edge[cnt].s=i;
				edge[cnt].cost=c;
				cnt++;
			}
		}
		build(N);
		sort(edge,edge+cnt,cmp);
		int ans=0;
		int count=1;
		for(int i=0;i<cnt;i++){
			int s=edge[i].s;
			int e=edge[i].e;
			int c=edge[i].cost;
			if(!same(s,e)){
				ans+=c;
				unite(s,e);
				count++;
			}
			if(count==N) break;
		}
		cout<<ans<<endl;
	}
	return 0;
}
