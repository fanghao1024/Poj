#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=5e5+10;
const int inf=0x3f3f3f3f;

ll N,D,K;
ll x[max_n],s[max_n];
ll v[max_n];
ll q[max_n];

bool check(ll mid){
    ll lpos=D-mid;
    ll rpos=D+mid;
    if(lpos<=0) lpos=1LL;
    memset(v,-inf,sizeof(v));
    v[0]=0;
    int f=0,r=-1;
    int cur=0;
    for(int i=1;i<=N;i++){
        for(;cur<i&&x[i]-x[cur]>=lpos;cur++){
            while(f<=r&&v[cur]>=v[q[r]]) r--;
            q[++r]=cur;
        }
        while(f<=r&&x[i]-x[q[f]]>rpos) f++;
        if(f<=r) v[i]=max(v[i],v[q[f]]+s[i]);
        if(v[i]>=K) return true;
    }
    return false;
}
int main(){
    scanf("%lld %lld %lld",&N,&D,&K);
    ll sum=0;
    for(int i=1;i<=N;i++){
        scanf("%lld %lld",&x[i],&s[i]);
        sum+=s[i]>0?s[i]:0;
    }
    if(sum<K) printf("-1\n");
    else{
        ll l=0,r=x[N];
        ll ans;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)){
                ans=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}