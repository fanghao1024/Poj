#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=2e6+10;

struct Cow{
    int p,a;
}cow[max_n];

bool cmp(const Cow& m,const Cow& n){
    return m.p<n.p;
}
int N,M;
int main(){
    scanf("%d %d",&N,&M);
    for(int i=0;i<M;i++) scanf("%d %d",&cow[i].p,&cow[i].a);
    sort(cow,cow+M,cmp);
    ll ans=0;
    int index=0;
    while(N){
        if(N>cow[index].a){
            ans+=cow[index].a*cow[index].p;
            N-=cow[index].a;
        }else{
            ans+=cow[index].p*N;
            N-=N;
        }
        index++;
    }
    printf("%lld\n",ans);
    return 0;
}