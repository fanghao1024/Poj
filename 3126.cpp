#include<stdio.h>
#include<vector>
#include<cmath>
#include<string.h>
#include<map>
#include<queue>
using namespace std;

typedef pair<int,int> P;
const int INF=0x3fffffff;
vector<int> prime;
bool factor[101];
bool prim[10000];
struct Edge{
	int to,cost;
	Edge(int to,int cost){
		this->to=to;
		this->cost=cost;
	}
	bool operator <(const Edge& temp)const{
		return this->cost>temp.cost;
	}
};
vector<Edge> edge[1080];
int dis[1080];
map<int,int> mp;
int get_diff(int x,int y){
	int ans=0;
	while(x>0){
		if((x%10)==(y%10)){
			ans++;
		}
		x=x/10;
		y=y/10;
	}
	return ans;
}
void get_4digit(){
	memset(factor,1,sizeof(factor));
	memset(prim,1,sizeof(prim));
	for(int i=2;i<100;i++){
		if(factor[i]){
			for(int j=2*i;j<100;j+=i){
				factor[j]=false;
			}
			for(int j=1000/i*i;j<10000;j+=i){
				prim[j]=false;
			}
		}
	}
	for(int i=1000;i<=9999;i++){
		if(prim[i]){
			prime.push_back(i);
			mp[i]=prime.size()-1;
		}
	}

	for(int i=0;i<prime.size();i++){
		for(int j=i+1;j<prime.size();j++){
			if(get_diff(prime[i],prime[j])==3){
				edge[i].push_back(Edge(j,1));
				edge[j].push_back(Edge(i,1));
			}
			
		}
	}
}

int Dijstra(int a,int b){
	//printf("%d %d %d %d\n",a,b,prime[a],prime[b]);
	for(int i=0;i<prime.size();i++){
		dis[i]=INF;
	}
	dis[a]=0;
	priority_queue<P,vector<P>,greater<P> >pq;
	pq.push(make_pair(0,a));
	while(!pq.empty()){
		P p=pq.top();
		int v=p.second;
		int d=p.first;
		
		pq.pop();
		//printf("%d===%d\n",dis[v],d);
		if(dis[v]<d) continue;
		//printf("----%d\n",d);
		//printf("%d~~~%d\n",v,b);
		if(v==b) return dis[b];
		//printf("----%d\n",edge[v].size());
		for(int i=0;i<edge[v].size();i++){
			if(dis[edge[v][i].to]>dis[v]+edge[v][i].cost){
				dis[edge[v][i].to]=dis[v]+edge[v][i].cost;
				pq.push(make_pair(dis[edge[v][i].to],edge[v][i].to));
			}
		}
	}
	return dis[b];
}

int main(){
	int T,a,b;
	scanf("%d",&T);
	get_4digit();
	
	while(T--){
		scanf("%d %d",&a,&b);
		int ans=Dijstra(mp[a],mp[b]);
		printf("%d\n",ans);
	}
	return 0;
}
