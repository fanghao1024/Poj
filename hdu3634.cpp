#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int max_n=22;
typedef long long ll;
struct Node{
    ll x1,y1,x2,y2,v;
    ll sum;
}node[max_n];

bool cmp(const Node& a,const Node& b){
    return a.v>b.v;
}

int T,N;
ll ans;
void dfs(ll x1,ll y1,ll x2,ll y2,int k,int i){
    while(k>=0&&(node[k].x1>=x2||node[k].x2<=x1||node[k].y1>=y2||node[k].y2<=y1)) k--;
    if(k==-1){node[i].sum+=(y2-y1)*(x2-x1)*node[i].v;return ;}
    if(x1<node[k].x1){
        dfs(x1,y1,node[k].x1,y2,k-1,i);
        x1=node[k].x1;
    }
    if(x2>node[k].x2){
        dfs(node[k].x2,y1,x2,y2,k-1,i);
        x2=node[k].x2;
    }
    if(y1<node[k].y1){
        dfs(x1,y1,x2,node[k].y1,k-1,i);
        y1=node[k].y1;
    }
    if(y2>node[k].y2){
        dfs(x1,node[k].y2,x2,y2,k-1,i);
        y2=node[k].y2;
    }
    
}
int main(){
    
    scanf("%d",&T);
    for(int caseNo=1;caseNo<=T;caseNo++){
        scanf("%d",&N);
        for(int i=0;i<N;i++){
            scanf("%lld %lld %lld %lld %lld",&node[i].x1,&node[i].y1,&node[i].x2,&node[i].y2,&node[i].v);
            node[i].sum=0;
        }
        sort(node,node+N,cmp);
        ans=0;
        for(int i=0;i<N;i++){
            dfs(node[i].x1,node[i].y1,node[i].x2,node[i].y2,i-1,i);
            ans+=node[i].sum;
        }
        printf("Case %d: %lld\n",caseNo,ans);
    }
    return 0;
}