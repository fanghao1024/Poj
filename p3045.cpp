#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
const int max_n=5e4+10;

typedef long long ll;
struct Cow{
    ll p,c;
}cow[max_n];
bool cmp(const Cow& a,const Cow& b){
    return a.c<b.c;
}
bool vis[max_n];
ll N,K,M;
priority_queue<ll,vector<ll>,greater<ll> > q1;
typedef pair<ll,ll> P;
priority_queue<P,vector<P>,greater<P> > q2,q3;
int main(){
    scanf("%lld %lld %lld",&N,&K,&M);
    for(int i=1;i<=N;i++){
        scanf("%lld %lld",&cow[i].p,&cow[i].c);
    }
    sort(cow+1,cow+1+N,cmp);
    ll sum=0;
    for(int i=1;i<=K;i++){
        sum+=cow[i].c;
        if(sum>M){
            printf("%d\n",i-1);
            return 0;
        }
        q1.push(cow[i].p-cow[i].c);
    }
    if(K==N){
        printf("%d\n",N);
        return 0;
    }
    for(int i=K+1;i<=N;i++){
        q2.push(make_pair(cow[i].c,i));
        q3.push(make_pair(cow[i].p,i));
    }
    ll ans=K;
    memset(vis,0,sizeof(vis));
    for(int i=K+1;i<=N;i++){
        while(vis[q2.top().second]) q2.pop();
        while(vis[q3.top().second]) q3.pop();
        ll temp2=q2.top().first;
        ll temp3=q3.top().first;
        if(temp2+q1.top()<temp3){
            int top=q2.top().second;
            q2.pop();
            sum+=temp2+q1.top();
            q1.pop();
            q1.push(cow[top].p-cow[top].c);
            vis[top]=1;
        }else{
            int top=q3.top().second;
            q3.pop();
            vis[top]=1;
            sum+=temp3;
        }
        ans++;
        if(sum>M){
            printf("%lld\n",ans-1);
            return 0;
        }
    }
    printf("%lld\n",ans);
    return 0;
}

