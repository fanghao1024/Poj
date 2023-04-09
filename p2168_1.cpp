#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

typedef long long ll;
struct Node{
    ll w,h;
    Node(ll _w,ll _h){
        w=_w;
        h=_h;
    }
    bool operator< (const Node& a) const{
        if(w!=a.w) return w>a.w;
        else return h>a.h;
    }
};

priority_queue<Node> q;
ll ans1,ans2,x,tempw,temph,N,K;
int main(){
    scanf("%lld %lld",&N,&K);
    for(int i=1;i<=N;i++){
        scanf("%lld",&x);
        q.push(Node(x,1));
    }
    if((N-1)%(K-1)){
        x=(K-1)-(N-1)%(K-1);
        while(x--){
            q.push(Node(0,1));
        }
    }
    ans1=0,ans2=0;
    while(q.size()>1){
        tempw=0;temph=-0x3f3f3f3f;
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
