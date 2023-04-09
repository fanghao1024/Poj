#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;

const int max_n=45000;
const ll MOD=1e9+7;
ll sum[max_n],mul[max_n];
ll fastpow(ll x,ll y){
    ll res=1;
    while(y){
        if(y&1) res=(res*x)%MOD;
        x=(x*x)%MOD;
        y>>=1;
    }
    return res;
}
ll inv(ll x){
    return fastpow(x,MOD-2);
}
void init(){
    sum[1]=0;
    mul[1]=1;
    for(int i=2;i<max_n;i++){
        sum[i]=sum[i-1]+i;
        mul[i]=(mul[i-1]*i)%MOD;
    }
}
int main(){
    int T;
    ll x;
    init();
    scanf("%d",&T);
    while(T--){
        scanf("%lld",&x);
        if(x==1){
            printf("1\n");
            continue;
        }
        int k=upper_bound(sum+1,sum+max_n,x)-sum-1;
        int m=x-sum[k];
        if(m==k){
            printf("%lld\n",((mul[k]*inv(2))%MOD)*(k+2)%MOD);
        }else{
            printf("%lld\n",(mul[k+1]*inv(k-m+1))%MOD);
        }
    }
    return 0;
}