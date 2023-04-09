#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=1e5+10;

ll pre[max_n];
ll limit[40];

int main(){
    int T,n;

    scanf("%d",&T);
    while(T--){
        scanf("%d", &n);
        ll x;
        pre[0]=0;
        for(int i=1;i<=n;i++){
            scanf("%lld",&x);
            pre[i]=pre[i-1]+x;
        }
        ll ans=0;
        for(int k=1;k<=34;k++){
           ll limitl=(k==1)?0:1LL<<(k-1),limitr=1LL<<k;
           int l=1,r=0;
           for(int i=1;i<=n;i++){
                l=max(l,i);
                while(l<=n&&pre[l]-pre[i-1]<limitl) l++;
                r=max(l-1,r);
                while(r+1<=n&&pre[r+1]-pre[i-1]<limitr) r++;
                if(l>r) continue;
                ans+=(ll)(i+l+i+r)*(r-l+1)*k/2;
           }
        }
        printf("%lld\n",ans);
    }
    

    return 0;
}