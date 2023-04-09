#include<cstdio>

typedef long long ll;

ll n,B;
int T;
ll ExtE(ll a,ll b,ll& x,ll& y){
    if(b==0){
        x=1;y=0;
        return a;
    }
    ll d=ExtE(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%lld %lld",&n,&B);
        ll a=B,b=9973;
        ll x,y;
        ll d=ExtE(a,b,x,y);
        x*=n;
        while(x<0) x+=b;
        printf("%lld\n",x%b);
    }
    return 0;
}