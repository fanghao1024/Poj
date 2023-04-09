#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=2e5+10;
ll w[max_n],v[max_n];
bool vis[max_n];
ll cnt[max_n],sum[max_n];
int left[max_n],right[max_n];
int N,M;
ll S,W;
ll check(ll mid){
    memset(vis,0,sizeof(vis));
    cnt[0]=sum[0]=0;
    for(int i=1;i<=N;i++){
        if(w[i]>=mid){
            cnt[i]=cnt[i-1]+1;
            sum[i]=sum[i-1]+v[i];
        }else{
            cnt[i]=cnt[i-1];
            sum[i]=sum[i-1];
        }
    }
    ll res=0;
    for(int i=1;i<=M;i++){
        res+=(sum[right[i]]-sum[left[i]-1])*(cnt[right[i]]-cnt[left[i]-1]);
    }
    return res;
}
int main(){
    scanf("%d %d %lld",&N,&M,&S);
    ll l=0,r=-1;
    for(int i=1;i<=N;i++){
        scanf("%lld %lld",&w[i],&v[i]);
        r=max(r,w[i]);
    }
    for(int i=1;i<=M;i++) scanf("%d %d",&left[i],&right[i]);
    ll ans=0x3f3f3f3f3f3f3f3f;
    r+=2;
    while(l<=r){
        ll mid=l+((r-l)>>1);
        ll res=check(mid);
        if(res==S){
            ans=0;
            break;
        }else if(res>S){
            ans=min(ans,llabs(res-S));
            l=mid+1;
        }else{
            ans=min(ans,llabs(res-S));
            r=mid-1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}