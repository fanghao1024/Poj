#include<stdio.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int max_N=5010;
const int INF=0x3fffffff;
struct Edge{
    int to;
    int cost;
};
vector<Edge> G[max_N];
int dist[max_N];
int dist2[max_N];
typedef pair<int,int> P;

int main(){
    int N,R;
    int A,B,D;
    scanf("%d %d",&N,&R);
    Edge edge;
    for(int i=0;i<R;i++){
        scanf("%d %d %d",&A,&B,&D);
        edge.to=B-1;
        edge.cost=D;
        G[A-1].push_back(edge);
        edge.to=A-1;
        G[B-1].push_back(edge);
    }
    fill(dist,dist+N,INF);
    fill(dist2,dist2+N,INF);
    priority_queue<P,vector<P>,greater<P> > que;
    dist[0]=0;

    que.push(make_pair(0,0));
    while(!que.empty()){
        P p=que.top();
        que.pop();
        int v=p.second;
        int d=p.first;
        if(dist2[v]<d){
            continue;
        }
    
        for(int i=0;i<G[v].size();i++){
            Edge e=G[v][i];
            int d2=e.cost+d;
            if(dist[e.to]>d2){
                swap(dist[e.to],d2);
                que.push(make_pair(dist[e.to],e.to));
            }
            if(dist2[e.to]>d2&&dist[e.to]<d2){
                dist2[e.to]=d2;
                que.push(make_pair(dist2[e.to],e.to));
            }
        }
    }
    printf("%d\n",dist2[N-1]);
    return 0;
}