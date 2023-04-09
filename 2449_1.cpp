#include<cstdio>
#include<cstring>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;

typedef pair<int,int> P;
const int max_n=1024,max_m=1e5+10;
int N,M,cnt1,cnt2;
int head1[max_n],head2[max_n];
struct Edge{
    int to,w;
    int nxt;
}edge1[max_m],edge2[max_m];
int num[max_n],h[max_n];
bool vis[max_n];
int S,T,K;
void init(){
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    cnt1=cnt2=0;
    memset(num,0,sizeof(num));
}
void add_edge1(int a,int b,int c){
    edge1[cnt1].to=b;
    edge1[cnt1].w=c;
    edge1[cnt1].nxt=head1[a];
    head1[a]=cnt1++;
}
void add_edge2(int a, int b, int c)
{
    edge2[cnt2].to = b;
    edge2[cnt2].w = c;
    edge2[cnt2].nxt = head2[a];
    head2[a] = cnt2++;
}
void bfs(){
    memset(h,0x3f,sizeof(h));
    memset(vis,0,sizeof(vis));
    h[T]=0;
    priority_queue<P,vector<P>,greater<P> > q;
    q.push(make_pair(0,T));
    while(!q.empty()){
        P p=q.top();
        q.pop();
        if(vis[p.second]) continue;
        vis[p.second] = 1;
        h[p.second]=p.first;
        for(int i=head2[p.second];i!=-1;i=edge2[i].nxt){
            int v=edge2[i].to;
            if(!vis[v]&&h[v]>h[p.second]+edge2[i].w){
                h[v]=h[p.second]+edge2[i].w;
                q.push(make_pair(h[v],v));
            }
        }
    }

}
struct Node{
    int to;
    int g,h;
    Node(){};
    Node(int _to,int _g,int _h){
        to=_to;g=_g;h=_h;
    }
    bool operator<(const Node& a) const{
        return g+h>a.g+a.h;
    }
};
int astar(){
    priority_queue<Node> q;
    q.push(Node(S,0,0));
    while(!q.empty()){
        Node node=q.top();
        q.pop();
        num[node.to]++;
        if(node.to==T&&num[node.to]==K){
            return node.g+node.h;
        }
       // if(num[node.to]>=K) continue;
        for(int i=head1[node.to];i!=-1;i=edge1[i].nxt){
            int v=edge1[i].to;
            q.push(Node(v,node.g+edge1[i].w,h[v]));
        }
    }
    return -1;
}
int main(){
    scanf("%d %d",&N,&M);
    init();
    int a,b,c;
    for(int i=0;i<M;i++){
        scanf("%d %d %d",&a,&b,&c);
        add_edge1(a,b,c);
        add_edge2(b,a,c);
    }
    scanf("%d %d %d",&S,&T,&K);
    if(S==T) K++;
    bfs();
    if(h[S]==0x3f3f3f3f) printf("-1\n");
    else{
        printf("%d\n",astar()); 
    }
    return 0;
}