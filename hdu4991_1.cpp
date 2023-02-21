#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int max_n=10010;
const int max_m=105;
const int MOD=123456789;
ll dp[max_n][max_m];
ll a[max_n],b[max_n];
int N,M,len;
int lowbit(int x){
    return x&(-x);
}
void add(int i,int j,int v){
    while(i<=len){
        dp[i][j]=(dp[i][j]+v)%MOD;
        i+=lowbit(i);
    }
}
ll query(int i,int j){
    int res=0;
    while(i){
        res=(res+dp[i][j])%MOD;
        i-=lowbit(i);
    }
    return res;
}
int main(){
    while(scanf("%d%d",&N,&M)!=EOF){
        for(int i=1;i<=N;i++){
            scanf("%lld",&a[i]);
            b[i]=a[i];
        }
        memset(dp,0,sizeof(dp));
        sort(b+1,b+1+N);
        len=unique(b+1,b+1+N)-b-1;
        for(int i=1;i<=N;i++){
            int pos=lower_bound(b+1,b+1+len,a[i])-b;
            add(pos,1,1);
            for(int j=2;j<=M;j++){
                ll sum=query(pos-1,j-1);
                add(pos,j,sum);
            }
        }
        printf("%lld\n",query(len,M));
    }
    return 0;
}