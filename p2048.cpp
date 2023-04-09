#include<cstdio>
#include<queue>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;

typedef long long ll;
const int max_n=5e5+10;

int n,k,L,R;
ll sum[max_n];
int st[max_n][30];
int Log2[max_n];

struct Node{
    int id,l,r,t;
    Node(){};
    Node(int _id,int _l,int _r,int _t){
        id=_id;l=_l;r=_r;t=_t;
    }
    bool operator<(const Node& node)const{
        return sum[t]-sum[id-1]<sum[node.t]-sum[node.id-1];
    }
};

priority_queue<Node> q;

void init(){
    Log2[0]=-1;
    for(int i=1;i<=n;i++) Log2[i]=Log2[i>>1]+1;
    for(int i=1;i<=n;i++) st[i][0]=i;
    for(int k=1;k<=Log2[n];k++){
        for(int i=1;i+(1<<k)-1<=n;i++){
            st[i][k]=sum[st[i][k-1]]>sum[st[i+(1<<(k-1))][k-1]]?st[i][k-1]:st[i+(1<<(k-1))][k-1];
        }
    }
}

int query(int l,int r){
    int k=Log2[r-l+1];
    return sum[st[l][k]]>sum[st[r-(1<<k)+1][k]]?st[l][k]:st[r-(1<<k)+1][k];
}
int main(){
    scanf("%d %d %d %d",&n,&k,&L,&R);
    sum[0]=0;
    ll x;
    for(int i=1;i<=n;i++){
        scanf("%lld",&x);
        sum[i]=sum[i-1]+x;
    }
    //for(int i=1;i<=n;i++) 
    //scanf("%lld", &sum[i]), sum[i] += sum[i - 1];
    init();
    
    for(int i=1;i<=n;i++){
        if(i+L-1<=n)
            q.push(Node(i, i+L-1,min(i+R-1,n), query(i+L-1, min(i + R - 1, n))));//, printf("###%d %d %d\n", i, min(i + R - 1, n), sum[query(i + L - 1, min(i + R - 1, n))] - sum[i - 1]);
    }
    ll ans;
    while(k--){
        Node node=q.top();
        q.pop();
        ans+=sum[node.t]-sum[node.id-1];
        //printf("~~%d\n",sum[node.t]-sum[node.id-1]);
        if(node.t!=node.l) q.push(Node(node.id,node.l,node.t-1,query(node.l,node.t-1)));
        if(node.t!=node.r) q.push(Node(node.id,node.t+1,node.r,query(node.t+1,node.r)));
        
    }
    printf("%lld\n",ans);
    return 0;
}