#include<cstdio>

typedef long long ll;
const int max_n=1e5+10;
ll mi[max_n],ai[max_n];
int n;
ll ExtE(ll a , ll b, ll& x,ll& y){
    if(b==0){
        x=1;y=0;
        return a;
    }
    ll d=ExtE(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
ll Mul(ll x,ll y,ll m){
    ll res=0;
    while(y){
        if(y&1) res=(res+x)%m;
        x=(x+x)%m;
        y>>=1;
    }
    return res;
}
ll solve(){
    ll x, y;
    ll m1=mi[1],a1=ai[1];
    ll m2,a2;
    for(int i=2;i<=n;i++){
        m2=mi[i];
        a2=ai[i];
        ll a=m1,b=m2,c=(a2-a1%m2+m2)%m2;
        ll d=ExtE(a,b,x,y);
        if(c%d) return -1;
        ll t=Mul(x,c/d,b/d);
        x=a1+a*t;
        m1=m2/d*m1;
        a1=(x%m1+m1)%m1;
    }
    return a1;
} 
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld %lld",&mi[i],&ai[i]);
    ll ans=solve();
    printf("%lld\n",ans);
    return 0;
}
