#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

const int max_n=210;
const int inf=0x3f3f3f3f;

int head[max_n],shelter[max_n],dist[max_n],pre[max_n],num[max_n],q[max_n];
bool vis[max_n];
int plan[max_n][max_n];
struct Node{
	int x,y;
	int count;
}a[max_n],b[max_n];
struct Edge{
	int to,nxt;
	int cap,flow;
	int cost;
}edge[(max_n*max_n)<<1];
int N,M,cnt;
void init(){
	memset(head,-1,sizeof(head));
	cnt=0;
}
void add_edge(int u,int v,int cap,int cost,int flow){
	edge[cnt].to=v;
	edge[cnt].cap=cap;
	edge[cnt].flow=flow;
	edge[cnt].cost=cost;
	edge[cnt].nxt=head[u];
	head[u]=cnt++;
}
void adde(int u,int v,int cap,int cost,int flow){
	add_edge(u,v,cap,cost,flow);
	add_edge(v,u,0,-cost,-flow);
}
int negative_loop(int s,int t){
	int f,r,top=-1;
	f=0;r=-1;
	memset(num,0,sizeof(num));
	memset(dist,0,sizeof(dist));
	memset(vis,true,sizeof(vis));//inqÊÇboolÀàÐÍµÄÊý×é£¬Ã¿¸öÔªËØÕ¼1×Ö½Ú£¬ËùÒÔ¿ÉÒÔÕâÑù
	memset(pre,-1,sizeof(pre));
	for(int i=s;i<=t;i++)
		q[++r]=i;
	while(f<=r){
		int u=q[r--];//Õ»Ê½Ð´·¨£¬r--¸Ä³Éf++¾ÍÊÇ¶ÓÁÐÁË£¬¶ÓÁÐÒª½«Êý×éÀ©´ó¡£
		vis[u]=false;//Êµ¼Ê²âÊÔÖÐ£¬ÓÃÕ»±È¶ÓÁÐÅÐ¶Ï¸ºÈ¦Ð§ÂÊ¸ü¸ß
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].to;
			if(edge[i].cap>edge[i].flow&&dist[v]>dist[u]+edge[i].cost){//ËÉ³Ú²Ù×÷
				dist[v]=dist[u]+edge[i].cost;
				pre[v]=i; //¼ÇÂ¼Ç°Çý
				if(!vis[v]){ //¶¥µãv²»ÔÚ¶ÓÄÚ
					q[++r]=v;
					vis[v]=true; //±ê¼Ç
					if(++num[v]>t+1)
						return v;
				}
			}
		} 
	}
	return -1;
}
int neg_loop(int s,int t){
	memset(dist,0,sizeof(dist));
	memset(vis,1,sizeof(vis));
	memset(pre,-1,sizeof(pre));
	memset(num,0,sizeof(num));
	int f=0,r=-1;
	for(int i=s;i<=t;i++) q[++r]=i;
	while(f<=r){
		int u=q[r--];
		vis[u]=false;
		for(int i=head[u];i!=-1;i=edge[i].nxt){
			int v=edge[i].to;
			if(edge[i].cap>edge[i].flow&&dist[v]>dist[u]+edge[i].cost){
				dist[v]=dist[u]+edge[i].cost;
				pre[v]=i;
				if(!vis[v]){
					q[++r]=v;
					vis[v]=true;
					if(++num[v]>t+1) return v;
				}
			}
		}
	}
	return -1;
}

int main(){
	scanf("%d %d",&N,&M);
		int s=0,t=N+M+1;
		init();
		for(int i=1;i<=N;i++){
			scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].count);
			adde(s,i,a[i].count,0,a[i].count);
		}	
		for(int i=1;i<=M;i++) scanf("%d %d %d",&b[i].x,&b[i].y,&b[i].count);
		int x;
		memset(shelter,0,sizeof(shelter));
		for(int i=1;i<=N;i++){
			for(int j=1;j<=M;j++){
				scanf("%d",&x);
				shelter[j]+=x;
				adde(i,j+N,inf,abs(a[i].x-b[j].x)+abs(a[i].y-b[j].y)+1,x);
			}	
		}
		for(int j=1;j<=M;j++){
			adde(j+N,t,b[j].count,0,shelter[j]);
		}
		int k=negative_loop(s,t);
		if(k!=-1){
			printf("SUBOPTIMAL\n");
			memset(vis,0,sizeof(vis));
			memset(plan,0,sizeof(plan));
			for(int i=pre[k];!vis[edge[i].to];i=pre[edge[i^1].to]){
				vis[edge[i].to]=1;
				k=edge[i].to;
			}
			for(int i=pre[k];;i=pre[edge[i^1].to]){
				edge[i].flow++;
				edge[i^1].flow--;
				if(edge[i^1].to==k) break;
			}
			for(int i=0;i<cnt;i++){
				if(edge[i^1].to>=1&&edge[i^1].to<=N&&edge[i].to>=N+1&&edge[i].to<=N+M){
					plan[edge[i^1].to][edge[i].to-N]=edge[i].flow;
				}
			}
			for(int i=1;i<=N;i++){
				for(int j=1;j<=M;j++){
					if(j-1) printf(" ");
					printf("%d",plan[i][j]);
				}
				printf("\n");
			}
		}else{
			printf("OPTIMAL\n");
		}
	
}


