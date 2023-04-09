#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=15;
const int inf=0x3f3f3f3f;

int head[max_n],cnt;
bool vis[max_n];
struct Edge{
    int to,imd;
    int p,r;
    int nxt;
}edge[max_n<<1];
int N,M,ans;
bool ok;
void init(){
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    cnt=0;
}
void add_edge(int a,int b,int c,int p,int r){
    edge[cnt].to=b;
    edge[cnt].imd=c;
    edge[cnt].p=p;
    edge[cnt].r=r;
    edge[cnt].nxt=head[a];
    head[a]=cnt++;
}
void dfs(int p,int dis){
    if(p==N){
        ok = true;
        if(ans>dis){
            ans=dis;
        }
        return ;
    }
    for(int i=head[p];i!=-1;i=edge[i].nxt){
        int v=edge[i].to;
        //if(!vis[v]){
            vis[v]=1;
            int temp=edge[i].r;
            if(vis[edge[i].imd]&&temp>edge[i].p){
                temp=edge[i].p;
            }
            dfs(v,dis+temp);
            vis[v]=0;
        //}
    }

}
int main(){
    scanf("%d %d",&N,&M);
    int a,b,c,p,r;
    init();
    for(int i=1;i<=M;i++){
        scanf("%d %d %d %d %d",&a,&b,&c,&p,&r);
        add_edge(a,b,c,p,r);
    }
    ans=inf;
    vis[1]=1;
    ok=false;
    dfs(1,0);
    if(ok) printf("%d\n",ans);
    else printf("impossible\n");
    return 0;
}