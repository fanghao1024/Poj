#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;

typedef long long ll;
map<ll,ll> dp[45];
ll N,M;
ll gcd(ll a,ll b){
    return b==0?a:gcd(b,a%b);
}
ll lcm(ll a,ll b){
    return a/gcd(a,b)*b;
}
void init(){
    dp[1][1]=1;
    for(int i=2;i<=40;i++){
        dp[i]=dp[i-1];
        dp[i][i]++;
        for(map<ll,ll>::iterator it=dp[i-1].begin();it!=dp[i-1].end();it++){
            dp[i][lcm(i,it->first)]+=dp[i-1][it->first];
        }
    }
}
int main(){
    int T;
    scanf("%d",&T);
    init();
    for(int i=1;i<=T;i++){
        scanf("%lld %lld",&N,&M);
        ll ans=0;
        for(map<ll,ll>::iterator it=dp[N].begin();it!=dp[N].end();it++){
            if(it->first>=M) ans+=it->second;
        }
        printf("Case #%d: %lld\n", i,ans);
    }
    return 0;
}