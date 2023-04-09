#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=305;
ll num[max_n];
int n;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&num[i]);
    sort(num,num+1+n);
    ll ans=0;
    int i=0,j=n;
    while(i<j){
        ans+=(num[j]-num[i])*(num[j]-num[i]);
        i++;
        if(i>=j) break;
        ans += (num[j] - num[i]) * (num[j] - num[i]);
        j--;
    }
    printf("%lld\n",ans);
    return 0;
}