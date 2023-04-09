#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

typedef long long ll;

const int inf=0x3f3f3f3f;
ll N,K;
struct Node{
    ll w,h;
    Node(){};
    Node(ll w_,ll h_){
        w=w_;
        h=h_;
    }
    bool operator<(const Node& a) const{
        if(w!=a.w) return w>a.w;
        else return h>a.h;
    }
};
priority_queue<Node> q;
int main(){
    ll x;
    scanf("%lld %lld",&N,&K);
    for(int i=1;i<=N;i++){
        scanf("%lld",&x);
        q.push(Node(x,1LL));
    }
    if((N-1)%(K-1)){
        x=(K-1)-(N-1)%(K-1);
        while(x--){
            q.push(Node(0,1));
        }
    }
    ll ans1=0,ans2=0;
    ll tempw,temph;
    while(q.size()>1){
        tempw=0;temph=-inf;
        for(int i=1;i<=K;i++){
            Node node=q.top();
            q.pop();
            tempw+=node.w;
            temph=max(temph,node.h);
        }
        q.push(Node(tempw,temph+1));
        ans1+=tempw;
        ans2=max(ans2,temph);
    }
    printf("%lld\n%lld\n",ans1,ans2);
    return 0;
}
