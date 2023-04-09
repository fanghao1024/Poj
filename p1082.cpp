#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;

ll ExtE(ll a,ll b,ll& x,ll &y){
    if(b==0){
        x=1;y=0;
        return a;
    }
    ll d=ExtE(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
int main(){
    ll a,b,x,y;
    scanf("%lld %lld",&a,&b);
    ll d=ExtE(a,b,x,y);
    printf("%lld\n",((x%b/d)+b/d)%(b/d));
    return 0;
}