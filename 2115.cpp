#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;

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
    ll A,B,C;
    int k;
    while(scanf("%lld %lld %lld %d",&A,&B,&C,&k)!=EOF){
    //while (cin>>A>>B>>C>>k)
    //{
        if(A==0&&B==0&&C==0&&k==0) break;
        if(B==A){
            printf("0\n");
            continue;
        }
        ll K=((ll)1)<<k;
        ll x,y;
        ll d=ExtE(C,K,x,y);
        if((B-A)%d)
            printf("FOREVER\n");
            //cout<<"FOREVER"<<endl;
        else{
            x=x*(B-A)/d;
            printf("%lld\n",(x%(K/d)+(K/d))%(K/d));
            //cout << (x % (K / d) + (K / d)) % (K / d)<<endl;
        }
    }
    return 0;
}