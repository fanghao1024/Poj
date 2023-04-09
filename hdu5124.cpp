#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> P;
const int max_n=1e5+10;

int T,N;
P lines[max_n<<1];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        
        for(int i=0;i<2*N;i++){
            scanf("%lld",&lines[i].first);
            lines[i].second=1;
            scanf("%lld", &lines[++i].first);
            lines[i].first++;
            lines[i].second=-1;
        }
        /*
                for (int i = 0; i < 2 * N; i++)
                {
                    scanf("%lld", &lines[i].first);
                    lines[i].second = 1;
                    scanf("%lld", &lines[++i].first);
                    lines[i].first++;
                    lines[i].second = -1;
                }
                */
        sort(lines,lines+2*N);
        ll ans=0,MAX=0;
        for(int i=0;i<2*N;i++){
            MAX+=lines[i].second;
            ans=max(ans,MAX);
        }
        printf("%lld\n",ans);
    }
    return 0;
}