#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=205;
const int inf=0x3f3f3f3f;
int dis[max_n][max_n],time[max_n],map[max_n][max_n];
struct Query{
	int x,y,t,id,ans;
}q[50010];;
bool cmp1(const Query& a,const Query& b){
	return a.t<b.t;
}
bool cmp2(const Query& a,const Query& b){
	return a.id<b.id;
}
int N,M,Q;
void floyd(){
	int k=0;
	for(int t=0;t<Q;t++){
		while(k<N&&time[k]<=q[t].t){
			for(int i=0;i<N;i++){
				for(int j=0;j<N;j++){
					if(dis[i][j]>dis[i][k]+dis[k][j]){
						dis[i][j]=dis[i][k]+dis[k][j];
					}
				}
			}
			k++;
		}
		int x=q[t].x,y=q[t].y;
		if(time[x]>q[t].t||time[y]>q[t].t||dis[x][y]==inf) q[t].ans=-1;
		else q[t].ans=dis[x][y];
		//printf("%d %d %d %d %d===%d\n",q[t].id,q[t].x,q[t].y,q[t].t,q[t].ans,dis[x][y]);
	}
}
int main(){
	scanf("%d %d",&N,&M);
	for(int i=0;i<N;i++) scanf("%d",&time[i]);
	memset(dis,0x3f,sizeof(dis));
	memset(map,0x3f,sizeof(map));
	for(int i=0;i<N;i++) dis[i][i]=0,map[i][i]=0;
	int x,y,w;
	while(M--){
		scanf("%d %d %d",&x,&y,&w);
		dis[x][y]=dis[y][x]=w;
	}
	scanf("%d",&Q);
	for(int i=0;i<Q;i++){
		scanf("%d %d %d",&q[i].x,&q[i].y,&q[i].t);
		q[i].id=i;
	}
	sort(q,q+Q,cmp1);
	floyd();
	sort(q,q+Q,cmp2);
	for(int i=0;i<Q;i++) printf("%d\n",q[i].ans);
	return 0;
}
